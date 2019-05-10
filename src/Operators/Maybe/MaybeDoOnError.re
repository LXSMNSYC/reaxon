
let operator: Utils.bifunc(Utils.consumer(exn), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;
  
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};