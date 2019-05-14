
let operator: Utils.func(MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;
      pub onError = x => obs#onComplete();
    });
  };
};