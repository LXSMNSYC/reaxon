
let operator: Utils.func(Utils.action, CompletableTypes.operator({..})) = (action) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (action()) {
        | () => obs#onComplete()
        | exception e => obs#onError(e)
      };

      state#cancel();
    }
  };
};