
let operator: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onCancel, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            onCancel();
            sub#cancel();
          }
        });
      };
  
      pub onComplete = obs#onComplete;
  
      pub onError = obs#onError;
    });
  };
};