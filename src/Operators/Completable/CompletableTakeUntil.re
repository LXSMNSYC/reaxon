
let operator = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onError(Exceptions.Cancellation);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};