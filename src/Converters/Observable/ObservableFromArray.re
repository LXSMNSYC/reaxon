let operator: Utils.func(array('a), ObservableTypes.operator({..}, 'a)) = (array) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel
    });

    array |> Array.iter(x => if (!state#isCancelled()) {
      obs#onNext(x);
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };
};