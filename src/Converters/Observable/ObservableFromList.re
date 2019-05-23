let operator: list('a) => ObservableTypes.operator('downstream, 'a) = (list) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    list |> List.iter(x => if (!state#isCancelled()) {
      obs#onNext(x);
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };
};