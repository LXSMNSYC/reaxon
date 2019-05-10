
let operator: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#unlink();

        source#subscribeWith({
          pub onSubscribe = state#link;

          pub onSuccess = obs#onSuccess;

          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    })
  }
};