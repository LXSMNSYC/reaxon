
let operator = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => switch (comparer(x, item)) {
        | result => obs#onSuccess(result)
        | exception e => obs#onError(e);
      };

      pub onError = obs#onError;
    })
  };
};