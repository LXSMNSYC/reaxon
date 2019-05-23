
let operator: (unit => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onFinally, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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