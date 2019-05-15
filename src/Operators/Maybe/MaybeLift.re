
let operator: (MaybeTypes.observer({..}, 'a) => MaybeTypes.observer({..}, 'b)) => MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};