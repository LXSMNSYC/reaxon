
let operator: Utils.bifunc(Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.t({..}, {..}, 'b)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => SingleError.operator(e)#subscribeWith(obs)
  };
};