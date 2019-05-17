let operator = (sources) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let size = ref(Array.length(sources));

    sources |> Array.iter(x => x#subscribeWith({
      val finished = ref(false);

      pub onSubscribe = state#add;
      pub onSuccess = x => {
        obs#onNext(x);
        if (!finished^) {
          finished := true;
          size := size^ - 1;

          if (size^ == 0) {
            obs#onComplete();
            state#cancel();
          }
        }
      };

      pub onError = e => {
        obs#onError(e);
        state#cancel();
      };
    }));
  };
};