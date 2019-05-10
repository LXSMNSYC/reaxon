
let operator: Utils.func(Utils.supplier(MaybeTypes.t({..}, 'a)), MaybeTypes.t({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => CompletableError.operator(e)#subscribeWith(obs);  
  };
};