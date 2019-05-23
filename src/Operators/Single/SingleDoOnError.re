
let operator = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = obs#onSuccess;
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};