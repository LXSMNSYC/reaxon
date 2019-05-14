let operator: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};
