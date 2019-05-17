
let operator = (supplier) => {
  pub subscribeWith = obs => switch (supplier()) {
    | source => source#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    })
    | exception e => SingleError.operator(e)#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};