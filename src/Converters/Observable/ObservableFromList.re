let operator: Utils.func(list('a), ObservableTypes.operator({..}, 'a)) = (list) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel
    });

    list |> List.iter(x => if (!state#isCancelled()) {
      obs#onNext(x);
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };
};