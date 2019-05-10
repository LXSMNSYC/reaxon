
let operator: Utils.func(Utils.supplier(SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => SingleError.operator(e)#subscribeWith(obs);
  };
};