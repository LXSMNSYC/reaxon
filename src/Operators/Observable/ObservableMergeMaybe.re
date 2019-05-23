let operator: ObservableTypes.s('source, MaybeTypes.s('c, 'a)) => ObservableTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let error = (e) => {
      obs#onError(e);
      state#cancel();
    };

    let expected = ref(0);
    let pending = ref(0);
    let outerDone = ref(false);

    source#subscribeWith({
      pub onSubscribe = state#add;
      pub onComplete = () => if (pending^ == 0) {
        obs#onComplete();
        state#cancel();
      } else {
        outerDone := true;
      };
      pub onError = error;
      pub onNext = x => {
        expected := expected^ + 1;
        pending := pending^ + 1;
        x#subscribeWith({
          pub onSubscribe = state#add;
          pub onComplete = () => {
            pending := pending^ - 1;

            if (outerDone^ && pending^ == 0) {
              obs#onComplete();
              state#cancel();
            }
          };

          pub onSuccess = (x) => {
            obs#onNext(x);
            this#onComplete();
          };

          pub onError = error;
        });
      };
    });
  };
};