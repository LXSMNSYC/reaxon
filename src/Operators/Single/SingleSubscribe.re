
let operator: Utils.bifunc(SingleTypes.recordObserver('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.subscription) = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;

    pub onSuccess = obs.onSuccess;

    pub onError = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};