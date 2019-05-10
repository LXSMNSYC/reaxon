
let operator: Utils.bifunc(Utils.consumer(exn), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = obs#onSuccess;
  
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};