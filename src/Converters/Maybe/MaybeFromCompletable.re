let operator = (completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    completable#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};