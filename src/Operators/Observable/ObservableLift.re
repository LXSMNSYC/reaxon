
let operator: (ObservableTypes.observer({..}, 'a) => ObservableTypes.observer({..}, 'b)) => ObservableTypes.t('source, 'downstream, 'a) => ObservableTypes.operator('upstream, 'b) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => ObservableError.operator(e)#subscribeWith(obs)
  };
};