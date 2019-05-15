let operator: 'a => MaybeTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, 'a) = (item, maybe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    maybe#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = obs#onSuccess;
      pub onComplete = () => obs#onSuccess(item);
      pub onError = obs#onError;
    });
  };
};