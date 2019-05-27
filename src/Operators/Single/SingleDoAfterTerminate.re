
let operator = (onTerminate, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };

      pub onError  = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
};