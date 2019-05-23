let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(Notification.Completable.OnComplete);
      pub onError = x => obs#onSuccess(Notification.Completable.OnError(x));
    });
  };
};