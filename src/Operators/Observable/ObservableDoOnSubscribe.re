let operator: Utils.bifunc(Utils.consumer(ObservableTypes.subscription), ObservableTypes.t({..}, {..}, 'a), ObservableTypes.operator({..}, 'a)) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
      pub onNext = obs#onNext;
    });
  };
};