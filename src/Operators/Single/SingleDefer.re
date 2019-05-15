
let operator: (unit => SingleTypes.t('source, 'upstream, 'a)) => SingleTypes.operator('downstream, 'a) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => SingleError.operator(e)#subscribeWith(obs);
  };
};