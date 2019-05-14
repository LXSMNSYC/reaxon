
let operator: Utils.bifunc(MaybeTypes.t({..}, {..}, 'a), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (resumeIfError, source) => {
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
        state#unlink();
        resumeIfError#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };
    });
  };
};