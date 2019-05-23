
let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(true);
      pub onSuccess = (x) => obs#onSuccess(false);
      pub onError = obs#onError;
    })
  };
};