
let operator = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith({
      pub onSubscribe = newObserver#onSubscribe;
      pub onComplete = newObserver#onComplete;
      pub onError = newObserver#onError;
    })
    | exception e => SingleError.operator(e)#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    })
  };
};