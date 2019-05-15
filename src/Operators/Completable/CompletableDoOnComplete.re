
let operator: (unit => unit) => CompletableTypes.t('source, 'upstream) => CompletableTypes.operator('downstream) = (onComplete, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        onComplete();
        obs#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};