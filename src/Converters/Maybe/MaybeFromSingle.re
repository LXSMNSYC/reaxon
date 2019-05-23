let operator = (single) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    single#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess  = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};