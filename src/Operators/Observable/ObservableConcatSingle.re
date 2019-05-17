let operator: ObservableTypes.s('source, SingleTypes.s('sub, 'a)) => ObservableTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let stack = ref([]);
    let running = ref(false);
    let requestComplete = ref(false);
    let origin = ref(None);

    source#subscribeWith({
      pub onSubscribe = sub => {
        origin := Some(sub)
        state#link(sub);
      };

      pub onComplete = () => {
        if (running^) {
          requestComplete := true;
        } else {
          obs#onComplete();
        }
      };

      pub onError = e => {
        obs#onError(e);
        state#cancel();
      };

      pri getNext = () => {
        state#unlink();
        let head = List.hd(stack^);
        stack := List.tl(stack^);

        let gn = this#getNext;

        head#subscribeWith({
          pub onSubscribe = state#link;
          pub onSuccess = (x) => {
            obs#onNext(x);
            if (List.length(stack^) > 0) {
              gn();
            } else if (requestComplete^) {
              obs#onComplete();
            } else {
              switch(origin^) {
                | Some(o) => state#link(o)
                | None => state#unlink()
              };
              running := false;
            }
          };
          pub onError = obs#onError;
        });
      };

      pub onNext = x => {
        stack := stack^ @ [x];
        if (!running^) {
          running := true;
          this#getNext();
        }
      };
    });
  };
};