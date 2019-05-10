let operator: Utils.func(MaybeTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, Notification.Maybe.t('a))) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => obs#onSuccess(Notification.Maybe.OnSuccess(x));

      pub onComplete = () => obs#onSuccess(Notification.Maybe.OnComplete);

      pub onError = x => obs#onSuccess(Notification.Maybe.OnError(x));
    });
  };
};