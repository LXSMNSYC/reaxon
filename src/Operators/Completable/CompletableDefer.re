
let operator = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    })
    | exception e => CompletableError.operator(e)#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });  
  };
};