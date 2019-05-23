let operator: ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
      pub onNext = obs#onNext;
    });
  };
};
