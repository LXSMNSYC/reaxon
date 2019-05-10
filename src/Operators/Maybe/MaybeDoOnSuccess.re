let operator: Utils.bifunc(Utils.consumer('a), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (onSuccess, source) => {
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
        onSuccess(x);
        obs#onSuccess(x);
      };

      pub onError = obs#onError;
    });
  };
};