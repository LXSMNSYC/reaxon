
let operator: (unit => 'a) => CompletableTypes.operator('downstream) = (supplier) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (supplier()) {
        | item => obs#onComplete()
        | exception e => obs#onError(e)
      };

      state#cancel();
    }
  };
};