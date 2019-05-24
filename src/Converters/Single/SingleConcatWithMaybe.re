
let operator: MaybeTypes.s('source, 'a) => SingleTypes.s('sub, 'a) => ObservableTypes.operator('downstream, 'a) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => {
        state#unlink();
        obs#onNext(x);
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onError = obs#onError;
          pub onSuccess = (x) => {
            obs#onNext(x);
            obs#onComplete();
          };
        });
      };

      pub onError = obs#onError;
    });
  };
};