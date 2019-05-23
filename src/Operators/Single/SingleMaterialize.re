let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = x => obs#onSuccess(Notification.Single.OnSuccess(x));
      pub onError = x => obs#onSuccess(Notification.Single.OnError(x));
    });
  };
};