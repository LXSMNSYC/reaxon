
let operator: Utils.bifunc(CompletableTypes.recordObserver, CompletableTypes.t({..}), CompletableTypes.subscription) = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;

    pub onComplete = obs.onComplete;

    pub onError = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};