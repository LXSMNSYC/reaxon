let operator: Utils.func(list(ObservableTypes.t({..}, {..}, 'a)), ObservableTypes.operator({..}, 'a)) = (sources) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let size = ref(List.length(sources));

    sources |> List.iter(x => x#subscribeWith({
      val finished = ref(false);
      pub onSubscribe = state#add;
      pub onComplete = () => if (!finished^) {
        finished := true;
        size := size^ - 1;
      };

      pub onError = e => {
        obs#onError(e);
        state#cancel();
      };

      pub onNext = obs#onNext;
    }));
  };
};