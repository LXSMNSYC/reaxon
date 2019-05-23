
let operator = (onComplete, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        onComplete();
        obs#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};