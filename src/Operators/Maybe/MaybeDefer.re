let operator = (supplier: unit => Types.Maybe.t('a)): Types.Maybe.t('a) => {
  subscribeWith: (obs: Types.Maybe.Observer.t('a)) => {
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

    let observer: Types.Maybe.Observer.t('a) = {
      onSubscribe: (sub: Types.Subscription.t) => {
        if (finished^ || subscribed^) {
          sub.cancel();
        } else {
          subscribed := true;
          subRef := Some(sub);
        }
      },
      onComplete: () => {
        if (!finished^ && subscribed^) {
          obs.onComplete();
          subscription.cancel();
        }
      },
      onSuccess: (x: 'a) => {
        if (!finished^ && subscribed^) {
          obs.onSuccess(x);
          subscription.cancel();
        }
      },
      onError: (x: exn) => {
        if (!finished^ && subscribed^) {
          obs.onError(x);
          subscription.cancel();
        } else {
          raise(x);
        }
      },
    };

    obs.onSubscribe(subscription);
    switch (supplier()) {
      | result => result.subscribeWith(observer)
      | exception e => observer.onError(e)
    };
  }
};