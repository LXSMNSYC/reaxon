
let operator: ('a => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.subscription = (onNext, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = () => ();
    pub onError = raise;
    pub onNext = onNext;
  });
  Utils.c2sub(state);
};