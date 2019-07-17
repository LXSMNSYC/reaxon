let operator = (mapper: 'a => 'b, source: Types.Single.t('a)): Types.Single.t('b) => {
  subscribeWith: (obs: Types.Single.Observer.t('b)) => {
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

    let observer: Types.Single.Observer.t('a) = {
      onSubscribe: (sub: Types.Subscription.t) => {
        if (finished^ || subscribed^) {
          sub.cancel();
        } else {
          subscribed := true;
          subRef := Some(sub);
        }
      },
      onSuccess: (x: 'a) => {
        if (!finished^ && subscribed^) {
          switch (mapper(x)) {
            | result => obs.onSuccess(result)
            | exception err => obs.onError(err)
          }
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
    source.subscribeWith(observer);
  }
};
