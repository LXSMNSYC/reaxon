let operator: Utils.func(SingleTypes.t({..}, {..}, Notification.Maybe.t('a)), MaybeTypes.operator({..}, 'a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => switch (x) {
        | Notification.Maybe.OnSuccess(item) => obs#onSuccess(item)
        | Notification.Maybe.OnComplete => obs#onComplete()
        | Notification.Maybe.OnError(item) => obs#onError(item)
      };

      pub onError = obs#onError;
    });
  };
};