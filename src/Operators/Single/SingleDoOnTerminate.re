
let operator = (onTerminate, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = (x) => {
        onTerminate();
        obs#onSuccess(x);
      };

      pub onError  = (x) => {
        onTerminate();
        obs#onError(x);
      };
    });
};