let operator = (source: Types.Single.t('a)): Types.Single.t(Types.Single.Notification.t('a)) => {
  subscribeWith: (obs: Types.Single.Observer.t(Types.Single.Notification.t('a))) => {
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
          obs.onSuccess(Types.Single.Notification.OnSuccess(x));
          subscription.cancel();
        }
      },
      onError: (x: exn) => {
        if (!finished^ && subscribed^) {
          obs.onSuccess(Types.Single.Notification.OnError(x));
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
