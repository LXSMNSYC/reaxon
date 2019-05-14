let operator: Utils.bifunc('a, MaybeTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = (item, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(item);
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};