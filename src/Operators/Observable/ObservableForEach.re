
let operator: ('a => unit) => ObservableTypes.t('source, 'upstream, 'a) => ObservableTypes.subscription = (onNext, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = () => ();
    pub onError = raise;
    pub onNext = onNext;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};