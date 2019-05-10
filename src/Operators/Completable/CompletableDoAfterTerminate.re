
let operator: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        obs#onComplete();
        onTerminate();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};