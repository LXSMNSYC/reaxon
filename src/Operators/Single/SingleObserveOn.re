
let operator = (scheduler, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(scheduler, {
      pub onSubscribe = obs#onSubscribe;

      pub onSuccess = (x) => state#link(scheduler#run(() => {
        obs#onSuccess(x);
      }));

      pub onError = (x) => state#link(scheduler#run(() => {
        obs#onError(x);
      }));
    })
};