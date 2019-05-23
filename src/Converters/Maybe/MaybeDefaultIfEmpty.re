let operator = (item, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(item);
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};