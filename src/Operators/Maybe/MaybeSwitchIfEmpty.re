let operator = (backup, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => backup#subscribeWith({
        pub onSubscribe = state#link;
        pub onComplete = obs#onComplete;
        pub onSuccess = obs#onSuccess;
        pub onError = obs#onError;
      });

      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};