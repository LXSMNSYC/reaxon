
let operator: MaybeTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, bool) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(true);
      pub onSuccess = (x) => obs#onSuccess(false);
      pub onError = obs#onError;
    })
  };
};