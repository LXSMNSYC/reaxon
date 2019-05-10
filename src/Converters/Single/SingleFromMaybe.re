let operator: Utils.func(MaybeTypes.t({..}, {..}, 'a), SingleTypes.operator({..} ,'t)) = (maybe) => {
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