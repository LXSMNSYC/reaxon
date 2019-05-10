
let operator: Utils.bifunc(Utils.action, MaybeTypes.t({..}, 'a), MaybeTypes.t({..}, 'a)) = (onTerminate, source) => {
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
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};