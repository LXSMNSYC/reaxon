
let operator = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => {
        state#unlink();
        obs#onNext(x);
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onSuccess = (v) => {
            obs#onNext(v);
            obs#onComplete();
          };
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    });
  };
};