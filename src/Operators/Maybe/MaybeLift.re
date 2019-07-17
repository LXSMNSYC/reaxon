let operator = (operator: Types.Maybe.Observer.t('b) => Types.Maybe.Observer.t('a), source: Types.Maybe.t('a)): Types.Maybe.t('b) => {
  subscribeWith: (obs: Types.Maybe.Observer.t('b)) => {
    switch (operator(obs)) {
      | result => source.subscribeWith(result)
      | exception exn => MaybeError.operator(exn).subscribeWith(obs);
    };
  }
};