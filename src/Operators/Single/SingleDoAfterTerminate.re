
let operator: Utils.bifunc(Utils.action, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };
  
      pub onError  = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};