
let operator = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith({
      pub onSubscribe = newObserver#onSubscribe;
      pub onSuccess = newObserver#onSuccess;
      pub onError = newObserver#onError;
    })
    | exception e => SingleError.operator(e)#subscribeWith({
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    })
  };
};

let operator = (operator: Types.Single.Observer.t('a) => Types.Single.Observer.t('b), source: Types.Single.t('a)): Types.Single.t('b) => {
  subscribeWith: (obs: Types.Single.Observer.t('a)) => {
    let subscribed = ref(false);
    let finished = ref(false);
    let subRef: ref(option(Types.Subscription.t)) = ref(None);
    
    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!finished^) {
          if (subscribed^) {
            switch (subRef^) {
            | Some(ref) => ref.cancel()
            | None => ()
            }
          }
          finished := true;
        }
      }
    };
  }
};