
let operator: (unit => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onFinally, source) => {
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
  
      pub onError  = (x) => {
        obs#onError(x);
        onFinally();
      };

      pub onNext = obs#onNext;
    });
  };
};