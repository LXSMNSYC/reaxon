
let operator: CompletableTypes.t('other, 'ostream) => CompletableTypes.t('source, 'upstream) => CompletableTypes.operator('downstream) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();

        source#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    })
  }
};