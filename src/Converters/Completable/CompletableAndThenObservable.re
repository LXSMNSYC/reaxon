
let operator: Utils.bifunc(ObservableTypes.t({..}, 'a), CompletableTypes.t({..}), ObservableTypes.t({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onError = obs#onError;
          pub onNext = obs#onNext;
        });
      };

      pub onError = obs#onError;
    });
  };
};