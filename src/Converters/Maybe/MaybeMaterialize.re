let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = x => obs#onSuccess(Notification.Maybe.OnSuccess(x));
      pub onComplete = () => obs#onSuccess(Notification.Maybe.OnComplete);
      pub onError = x => obs#onSuccess(Notification.Maybe.OnError(x));
    });
  };
};