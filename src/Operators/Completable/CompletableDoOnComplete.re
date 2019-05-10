
let operator: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onComplete, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        onComplete();
        obs#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};