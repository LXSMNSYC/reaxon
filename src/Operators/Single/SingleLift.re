
let operator = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => Utils.makeCSO(source, {
      pub onSubscribe = newObserver#onSubscribe;
      pub onSuccess = newObserver#onSuccess;
      pub onError = newObserver#onError;
    })
    | exception e => Utils.makeCSO(SingleError.operator(e), {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};