
let operator: ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, bool) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(true);
      pub onNext = () => {
        obs#onSuccess(false);
        state#cancel();
      };
      pub onError = obs#onError;
    })
  };
};