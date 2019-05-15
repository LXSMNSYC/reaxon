
let operator: (unit => CompletableTypes.t({..}, {..})) => CompletableTypes.operator('downstream) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => CompletableError.operator(e)#subscribeWith(obs);  
  };
};