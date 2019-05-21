
let operator: (unit => ObservableTypes.s('source, 'a)) => ObservableTypes.operator('downstream, 'a) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => ObservableError.operator(e)#subscribeWith(obs);
  };
};