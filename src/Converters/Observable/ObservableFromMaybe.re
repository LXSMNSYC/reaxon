let operator: MaybeTypes.t('source, 'a) => ObservableTypes.operator('downstream, 'a) = (maybe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    maybe#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        obs#onNext(x);
        obs#onComplete();
      };

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};