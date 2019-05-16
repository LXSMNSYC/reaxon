
let operator: (SingleTypes.observer('from, 'a) => SingleTypes.observer('result, 'b)) => SingleTypes.t('source, 'a) => SingleTypes.operator('upstream, 'b) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};