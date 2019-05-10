
let operator: Utils.bifunc(Utils.consumer(exn), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = obs#onComplete;
  
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};