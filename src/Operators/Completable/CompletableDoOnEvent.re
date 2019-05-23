
let operator = (onEvent, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        onEvent(None);
        obs#onComplete();
      };
  
      pub onError = (x) => {
        onEvent(Some(x));
        obs#onError(x);
      };
    });
  };
};