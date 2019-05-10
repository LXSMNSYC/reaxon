let operator: Utils.func(MaybeTypes.t({..}, {..}, 'a), ObservableTypes.t({..}, 'a)) = (maybe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    maybe#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        obs#onNext(x);
        obs#onComplete();
      };

      pub onComplete = obs#onComplete;

      pub onError = obs#onError;
    });
  };
};