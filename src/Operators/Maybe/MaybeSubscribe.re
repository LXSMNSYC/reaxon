
let operator = (onSuccess, onComplete, onError, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;
    pub onComplete = onComplete;
    pub onSuccess = onSuccess;
    pub onError = onError;
  });
  Utils.c2sub(state);
};