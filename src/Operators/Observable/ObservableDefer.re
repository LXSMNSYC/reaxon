
let operator: Utils.func(Utils.supplier(ObservableTypes.t({..}, {..}, 'a)), ObservableTypes.operator({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => ObservableError.operator(e)#subscribeWith(obs);
  };
};