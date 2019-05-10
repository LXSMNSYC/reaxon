let operator: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), ObservableTypes.t({..}, 'a)) = (single) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    single#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        obs#onNext(x);
        obs#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};