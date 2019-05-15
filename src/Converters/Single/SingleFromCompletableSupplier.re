let operator: (unit => 'a) => CompletableTypes.t('source, 'upstream) => SingleTypes.operator('downstream, 'a) = (supplier, completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completable#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => switch(supplier()) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e)
      };

      pub onError = obs#onError;
    });
  };
};