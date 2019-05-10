
let operator: Utils.func(Utils.supplier(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => SingleError.operator(e)#subscribeWith(obs);
  };
};