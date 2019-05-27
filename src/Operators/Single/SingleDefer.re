
let operator = (supplier) => {
  pub subscribeWith = obs => switch (supplier()) {
    | source => Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    })
    | exception e => Utils.makeCSO(SingleError.operator(e), {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};