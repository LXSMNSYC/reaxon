let operator: (unit => 'a) => SingleTypes.operator('downstream, 'a) = (supplier) => {
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