let operator: (MaybeTypes.subscription => unit) => MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};