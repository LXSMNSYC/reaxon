let operator: int => int => int => ObservableTypes.operator('downstream, int) = (start, size, stepSize) => {
  pri produce = (iterator, current) => if (current <= size) {
    iterator(current);
    this#produce(iterator, current + stepSize);
  };
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    this#produce(x => if (!state#isCancelled()) {
      obs#onNext(x);
    }, start);

    if (!state#isCancelled()) {
      obs#onComplete();
    }
  };
};