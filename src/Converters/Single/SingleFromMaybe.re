let operator: MaybeTypes.s('source, 'a) => SingleTypes.operator('downstream ,'a) = (maybe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    maybe#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = obs#onSuccess;
      pub onComplete = () => obs#onError(Exceptions.NoSuchElement);
      pub onError = obs#onError;
    });
  };
};