
let operator: (unit => ObservableTypes.t('source, 'upstream, 'a)) => ObservableTypes.operator('downstream, 'a) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => ObservableError.operator(e)#subscribeWith(obs);
  };
};