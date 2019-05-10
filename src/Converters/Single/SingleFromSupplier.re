let operator: Utils.func(Utils.supplier('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (supplier) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (supplier()) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e)
      };
      state#cancel();
    }
  };
};