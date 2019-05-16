
let operator: (unit => unit) => CompletableTypes.t('source) => CompletableTypes.operator('downstream) = (onFinally, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => state#link({
        pub isCancelled = sub#isCancelled;
        pub cancel = () => {
          sub#cancel();
          onFinally();
        }
      });
  
      pub onComplete = () => {
        obs#onComplete();
        onFinally();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
  };
};