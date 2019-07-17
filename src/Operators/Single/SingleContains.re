let operator = (item: 'a, comparer: ('a, 'a) => bool, source: Types.Single.t('a)): Types.Single.t(bool) => {
  subscribeWith: (obs: Types.Single.Observer.t('a)) => {
    let subscribed = ref(false);
    let finished = ref(false);
    let subRef: ref(option(Types.Subscription.t)) = ref(None);

    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (subscribed^ && !finished^) {
          switch (subRef^) {
            | Some(c) => c.cancel()
            | None => ()
          };
        }
        finished := true;
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
        if (subscribed^ && !finished^) {
          switch (comparer(x, item)) {
            | result => obs.onSuccess(result)
            | exception e => obs.onError(e);
          };
          subscription.cancel();
        }
      },

      onError: (x: exn) => {
        if (subscribed^ && !finished^) {
          obs.onError(x);
          subscription.cancel();
        }
      },
    }

    obs.onSubscribe(subscription);
    source.subscribeWith(observer);
  }
};