let operator = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};