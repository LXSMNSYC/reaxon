
let operator: Utils.func('a, SingleTypes.t({..}, 'a)) = (value) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onSuccess(value);
      state#cancel();
    }
  };
};