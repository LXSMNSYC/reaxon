let operator: Utils.bifunc(Utils.consumer(MaybeTypes.subscription), MaybeTypes.t({..}, 'a), MaybeTypes.t({..}, 'a)) = (onSubscribe, source) => {
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