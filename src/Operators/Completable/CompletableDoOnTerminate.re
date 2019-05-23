
let operator = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        onTerminate();
        obs#onComplete();
      };
  
      pub onError  = (x) => {
        onTerminate();
        obs#onError(x);
      };
    });
  };
};