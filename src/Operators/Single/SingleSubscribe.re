
let operator = (observer: SingleTypes.recordObserver('a), source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onSuccess = observer.onSuccess;
    pub onError = observer.onError;
  });
  
  Utils.c2sub(state);
};