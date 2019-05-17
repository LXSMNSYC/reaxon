
let operator = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith({
      pub onSubscribe = newObserver#onSubscribe;
      pub onSuccess = newObserver#onSuccess;
      pub onError = newObserver#onError;
    })
    | exception e => SingleError.operator(e)#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    })
  };
};