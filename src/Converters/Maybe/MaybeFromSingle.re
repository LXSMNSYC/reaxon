let operator: Utils.func(SingleTypes.t({..}, 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = (completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completable#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess  = obs#onSuccess;

      pub onError = obs#onError;
    });
  };
};