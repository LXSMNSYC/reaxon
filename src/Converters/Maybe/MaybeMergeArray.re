let operator = (sources) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let size = ref(Array.length(sources));
    if (size^ > 0) {
      sources |> Array.iter(x => x#subscribeWith({
        val finished = ref(false);

        pub onSubscribe = state#add;

        pub onComplete = () => if (!finished^) {
          finished := true;
          size := size^ - 1;

          if (size^ == 0) {
            obs#onComplete();
            state#cancel();
          }
        };

        pub onSuccess = x => {
          obs#onNext(x);
          this#onComplete();
        };

        pub onError = e => {
          obs#onError(e);
          state#cancel();
        };
      }));
    } else {
      obs#onComplete();
      state#cancel();
    }
  };
};