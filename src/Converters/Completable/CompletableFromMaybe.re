let operator: Utils.func(MaybeTypes.t({..}, {..}, 'a), CompletableTypes.operator({..})) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = x => obs#onComplete();
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};