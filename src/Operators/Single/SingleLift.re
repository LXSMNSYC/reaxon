let operator = (operator: Types.Single.Observer.t('b) => Types.Single.Observer.t('a), source: Types.Single.t('a)): Types.Single.t('b) => {
  subscribeWith: (obs: Types.Single.Observer.t('b)) => {
    switch (operator(obs)) {
      | result => source.subscribeWith(result)
      | exception exn => SingleError.operator(exn).subscribeWith(obs);
    };
  }
};