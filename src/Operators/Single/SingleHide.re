let operator = (source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
};
