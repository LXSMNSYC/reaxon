
let operator = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(false);

      pub onSuccess = (x) => switch (comparer(x, item)) {
        | result => obs#onSuccess(result)
        | exception e => obs#onError(e);
      };

      pub onError = obs#onError;
    })
  };
};