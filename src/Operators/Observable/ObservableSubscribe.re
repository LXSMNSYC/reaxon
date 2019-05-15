
let operator: ObservableTypes.recordObserver('a) => ObservableTypes.t('source, 'upstream, 'a) => ObservableTypes.subscription = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = obs.onComplete;
    pub onError = obs.onError;
    pub onNext = obs.onNext;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};