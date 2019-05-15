
let operator: MaybeTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, int) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(0);
      pub onSuccess = (x) => obs#onSuccess(1);
      pub onError = obs#onError;
    })
  };
};