let operator: Utils.bifunc('a, CompletableTypes.t({..}), SingleTypes.t({..}, 'a)) = (item, completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completable#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(item);

      pub onError = obs#onError;
    });
  };
};