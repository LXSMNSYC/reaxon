
let operator = (onSubscribe, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = (state) => {
        onSubscribe(state);
        obs#onSubscribe(state);
      };

      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
};