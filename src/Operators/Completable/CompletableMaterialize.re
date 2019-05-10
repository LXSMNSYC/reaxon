let operator: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, Notification.Completable.t)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => obs#onSuccess(Notification.Completable.OnComplete);

      pub onError = x => obs#onSuccess(Notification.Completable.OnError(x));
    });
  };
};