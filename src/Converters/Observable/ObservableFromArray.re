let operator: array('a) => ObservableTypes.operator('downstream, 'a) = (array) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(Utils.c2sub(state));

    array |> Array.iter(x => if (!state#isCancelled()) {
      obs#onNext(x);
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };
};