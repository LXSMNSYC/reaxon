
let operator: (unit => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        obs#onComplete();
        onTerminate();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onTerminate();
      };

      pub onNext = obs#onNext;
    });
  };
};