
let operator: MaybeTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, bool) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(false);
      pub onSuccess = (x) => obs#onSucces(true);
      pub onError = obs#onError;
    })
  };
};