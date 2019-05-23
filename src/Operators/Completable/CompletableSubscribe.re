
let operator = (obs: CompletableTypes.recordObserver, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = obs.onComplete;
    pub onError = obs.onError;
  });
  Utils.c2sub(state);
};