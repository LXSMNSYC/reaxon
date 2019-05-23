let operator = (onSuccess, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        onSuccess(x);
        obs#onSuccess(x);
      };

      pub onError = obs#onError;
    });
  };
};