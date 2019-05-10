let operator: Utils.func(SingleTypes.t({..}, Notification.Single.t('a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (source) => {
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