
let operator = (onSuccess, onComplete, onError, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = onComplete;
    pub onSuccess = onSuccess;
    pub onError = onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};