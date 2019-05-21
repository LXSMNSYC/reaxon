
let operator: ('a => bool) => ObservableTypes.s('source, 'a) => ObservableTypes.subscription = (onNext, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = () => ();
    pub onError = raise;
    pub onNext = x => if (!onNext(x)) {
      state#cancel();
    };
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};