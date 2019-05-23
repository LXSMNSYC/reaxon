
let operator: (exn => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onNext = obs#onNext;
  
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};