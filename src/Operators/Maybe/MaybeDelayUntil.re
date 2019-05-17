
let operator = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();

        source#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onSuccess = obs#onSuccess;
          pub onError = obs#onError;
        });
      };

      pub onSuccess = (x) => this#onComplete();

      pub onError = obs#onError;
    })
  }
};