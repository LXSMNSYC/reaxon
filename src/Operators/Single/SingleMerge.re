let operator: Utils.func(SingleTypes.t({..}, SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a)) = (source) => {
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
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };
      pub onError = obs#onError;
    })
  };
};