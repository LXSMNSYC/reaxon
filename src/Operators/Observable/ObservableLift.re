
let operator: (ObservableTypes.observer({..}, 'a) => ObservableTypes.observer({..}, 'b)) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('upstream, 'b) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => ObservableError.operator(e)#subscribeWith(obs)
  };
};