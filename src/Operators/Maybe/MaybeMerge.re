let operator: Utils.func(MaybeTypes.t({..}, {..}, MaybeTypes.t({..}, {..}, 'a)), MaybeTypes.operator({..}, 'a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = x => {
        state#unlink();
        x#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    })
  };
};