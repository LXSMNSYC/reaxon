
let operator = (onError, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError  = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
};