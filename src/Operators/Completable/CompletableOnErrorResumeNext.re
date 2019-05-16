
let operator: CompletableTypes.t('other) => CompletableTypes.t('source) => CompletableTypes.operator('downstream) = (resumeIfError, source) => {
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
        state#unlink();
        resumeIfError#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onError = obs#onError;
        });
      };
    });
  };
};