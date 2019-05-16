let operator: SingleTypes.t('source, Notification.Single.t('a)) => SingleTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => switch (x) {
        | Notification.Single.OnSuccess(item) => obs#onSuccess(item)
        | Notification.Single.OnError(item) => obs#onError(item)
      };

      pub onError = obs#onError;
    });
  };
};