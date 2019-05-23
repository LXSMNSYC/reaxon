
let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(0);
      pub onSuccess = (x) => obs#onSuccess(1);
      pub onError = obs#onError;
    })
  };
};