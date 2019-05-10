
let operator: Utils.func(Utils.supplier(CompletableTypes.t({..})), CompletableTypes.t({..})) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => CompletableError.operator(e)#subscribeWith(obs);  
  };
};