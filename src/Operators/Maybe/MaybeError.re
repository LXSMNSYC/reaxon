let operator = (value: exn): Types.Maybe.t('a) => {
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

    obs.onSubscribe(subscription);

    if (!finished^) {
      obs.onError(value);
      subscription.cancel();
    }
  }
};