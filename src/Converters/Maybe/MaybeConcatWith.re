
let operator = (other, source) => {
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
          pub onSuccess = (v) => {
            obs#onNext(v);
            obs#onComplete();
          };
          pub onError = obs#onError;
        });
      };

      pub onSuccess = x => {
        obs#onNext(x);
        this#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};