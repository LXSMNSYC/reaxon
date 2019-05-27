
let operator = (onSuccess, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onSuccess(x);
      };
      pub onError = obs#onError;
    });
};