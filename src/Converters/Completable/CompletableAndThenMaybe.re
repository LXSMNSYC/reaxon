
let operator: Utils.bifunc(MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a), CompletableTypes.t({..}), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    });
  };
};