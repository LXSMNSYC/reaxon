let operator: 'a => ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (default, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(default);
      pub onError = obs#onError;
      pub onNext = x => {
        obs#onSuccess(x);
        state#cancel();
      };
    });
  };
};