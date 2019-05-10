let operator: Utils.bifunc(Utils.consumer(CompletableTypes.subscription), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (onSubscribe, source) => {
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

      pub onError = obs#onError;
    });
  };
};