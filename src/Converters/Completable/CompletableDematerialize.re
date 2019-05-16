let operator: SingleTypes.t('source, Notification.Completable.t) => CompletableTypes.operator('downstream) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => switch (x) {
        | Notification.Completable.OnComplete => obs#onComplete()
        | Notification.Completable.OnError(item) => obs#onError(item)
      };

      pub onError = obs#onError;
    });
  };
};