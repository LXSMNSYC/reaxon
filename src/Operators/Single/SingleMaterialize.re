let operator = (source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = x => obs#onSuccess(Notification.Single.OnSuccess(x));
      pub onError = x => obs#onSuccess(Notification.Single.OnError(x));
    });
};