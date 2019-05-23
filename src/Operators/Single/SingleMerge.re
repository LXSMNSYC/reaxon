let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = x => {
        state#unlink();
        x#subscribeWith({
          pub onSubscribe = state#link;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };
      pub onError = obs#onError;
    })
  };
};