
let operator: (unit => CompletableTypes.t('source)) => CompletableTypes.operator('downstream) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => CompletableError.operator(e)#subscribeWith(obs);  
  };
};