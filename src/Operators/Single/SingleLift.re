
let operator: Utils.bifunc(Utils.func(SingleTypes.observer({..}, 'a), SingleTypes.observer({..}, 'b)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'b)) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};