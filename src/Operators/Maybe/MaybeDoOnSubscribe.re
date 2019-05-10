let operator: Utils.bifunc(Utils.consumer(MaybeTypes.subscription), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onComplete = obs#onComplete;

      pub onSuccess = obs#onSuccess;

      pub onError = obs#onError;
    });
  };
};