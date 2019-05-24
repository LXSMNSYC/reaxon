let operator: ('a => list('b)) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'b) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let stack = ref([]);
    let running = ref(false);
    let requestComplete = ref(false);
    source#subscribeWith({
      pub onSubscribe = state#link;

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
        let head = List.hd(stack^);
        stack := List.tl(stack^);

        let gn = this#getNext;

        switch (mapper(head)) {
          | item => {
            item |> List.iter(i => 
              if (!state#isCancelled()) {
                obs#onNext(i);
              }
            );

            if (!state#isCancelled()) {
              if (List.length(stack^) > 0) {
                gn();
              } else if (requestComplete^) {
                obs#onComplete();
              }
            }
          }
          | exception e => {
            obs#onError(e);
            state#cancel();
          } 
        }
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