
let operator: Utils.bifunc(Utils.consumer('a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = (onSuccess, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
  
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onSuccess(x);
      };
  
      pub onError = obs#onError;
    });
  };
};