let operator = (operator: Types.Single.Observer.t('a) => Types.Single.Observer.t('b), source: Types.Single.t('a)): Types.Single.t('b) => {
  subscribeWith: (obs: Types.Single.Observer.t('a)) => {
    switch (operator(obs)) {
      | result => source.subscribeWith(result)
      | exception exn => SingleError.operator(exn).subscribeWith(obs);
    };
  }
};