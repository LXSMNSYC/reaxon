
let operator: MaybeTypes.s('sub, 'a) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onSuccess = x => {
            obs#onNext(x);
            obs#onComplete();
          };
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
      pub onNext = obs#onNext;
    });
  };
};