
let operator: Utils.bifunc(MaybeTypes.recordObserver('a), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.subscription) = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;

    pub onComplete = obs.onComplete;
    pub onSuccess = obs.onSuccess;
    pub onError = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};