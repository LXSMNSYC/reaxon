
let operator: (unit => MaybeTypes.t('source, 'upstream, 'a)) => MaybeTypes.operator('downstream, 'a) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => CompletableError.operator(e)#subscribeWith(obs);  
  };
};