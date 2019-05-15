
let operator: 'a => ObservableTypes.operator('downstream, 'a) = (value) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onNext(value);
      obs#onComplete();
      state#cancel();
    }
  };
};