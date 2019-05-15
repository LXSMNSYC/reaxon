
let operator: SingleTypes.t('source, 'upstream, 'a) => CompletableTypes.operator('downstream) = (single) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    single#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => obs#onComplete();
      pub onError = obs#onError;
    })
  };
};