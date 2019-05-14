
let operator: Utils.bifunc(Utils.func(MaybeTypes.t({..}, {..}, 'a), MaybeTypes.t({..}, {..}, 'b)), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'b)) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};