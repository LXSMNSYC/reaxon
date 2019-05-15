
let operator: (SingleTypes.observer({..}, 'a) => SingleTypes.observer({..}, 'b)) => SingleTypes.t('source, 'downstream, 'a) => SingleTypes.operator('upstream, 'b) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};