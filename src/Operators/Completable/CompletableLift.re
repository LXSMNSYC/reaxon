let operator = (operator: Types.Completable.Observer.t => Types.Completable.Observer.t, source: Types.Completable.t): Types.Completable.t => {
  subscribeWith: (obs: Types.Completable.Observer.t) => {
    switch (operator(obs)) {
      | result => source.subscribeWith(result)
      | exception exn => CompletableError.operator(exn).subscribeWith(obs);
    };
  }
};