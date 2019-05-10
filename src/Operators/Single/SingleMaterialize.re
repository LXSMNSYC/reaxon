let operator: Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, Notification.Single.t('a))) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => obs#onSuccess(Notification.Single.OnSuccess(x));

      pub onError = x => obs#onSuccess(Notification.Single.OnError(x));
    });
  };
};