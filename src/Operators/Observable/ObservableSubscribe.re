
let operator: ObservableTypes.recordObserver('a) => ObservableTypes.s('source, 'a) => ObservableTypes.subscription = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = obs.onComplete;
    pub onError = obs.onError;
    pub onNext = obs.onNext;
  });
  Utils.c2sub(state);
};