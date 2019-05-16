
let operator: SingleTypes.t('backup, 'a) => SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (resumeIfError, source) => {
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
        state#unlink();
        resumeIfError#subscribeWith({
          pub onSubscribe = state#link;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };
    });
  };
};