
let operator: Utils.func(exn, SingleTypes.t({..}, 'a)) = (err) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onError(err);
      state#cancel();
    }
  };
};