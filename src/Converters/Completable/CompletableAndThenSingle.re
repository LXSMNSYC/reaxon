
let operator: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), CompletableTypes.t({..}), SingleTypes.operator({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    });
  };
};