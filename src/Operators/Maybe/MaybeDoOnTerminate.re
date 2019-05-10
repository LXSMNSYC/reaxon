
let operator: Utils.bifunc(Utils.action, MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        onTerminate();
        obs#onComplete();
      };
  
      pub onSuccess = (x) => {
        onTerminate();
        obs#onSuccess(x);
      };
  
      pub onError  = (x) => {
        onTerminate();
        obs#onError(x);
      };
    });
  };
};