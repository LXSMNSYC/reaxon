let operator = (sources) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let size = ref(List.length(sources));

    sources |> List.iter(x => x#subscribeWith({
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
  };
};