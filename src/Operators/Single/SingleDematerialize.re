let operator = (source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = x => switch (x) {
        | Notification.Single.OnSuccess(item) => obs#onSuccess(item)
        | Notification.Single.OnError(item) => obs#onError(item)
      };
      pub onError = obs#onError;
    });
};