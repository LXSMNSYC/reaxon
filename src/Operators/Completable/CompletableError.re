let operator = (value: exn): Types.Completable.t => {
  subscribeWith: (obs: Types.Completable.Observer.t) => {
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