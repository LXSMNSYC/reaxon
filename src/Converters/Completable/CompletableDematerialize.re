let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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