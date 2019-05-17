let operator: SingleTypes.s('other, 'a) => MaybeTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a) = (backup, source) => {
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
        pub onSuccess = obs#onSuccess;
        pub onError = obs#onError;
      });

      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};