let operator = (observable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    observable#subscribeWith({
      pub onSubscribe = state#link;
      pub onNext = x => ();
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};