let operator: (ObservableTypes.subscription => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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