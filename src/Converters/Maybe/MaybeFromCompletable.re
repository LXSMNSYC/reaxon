let operator: Utils.func(CompletableTypes.t({..}, {..}), MaybeTypes.operator({..}, 'a)) = (completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completable#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;

      pub onError = obs#onError;
    });
  };
};