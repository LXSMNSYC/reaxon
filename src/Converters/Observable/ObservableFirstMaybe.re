let operator: ObservableTypes.t('source, 'a) => MaybeTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
      pub onNext = x => {
        obs#onSuccess(x);
        state#cancel();
      };
    });
  };
};