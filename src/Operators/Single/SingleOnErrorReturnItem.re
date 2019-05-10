
let operator: Utils.bifunc('a, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (item, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = (x) => obs#onSuccess(item);
    });
  };
};