let operator = (observer: Types.Single.Observer.Lambda.t('a), source: Types.Single.t('a)): Types.Subscription.t => {
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

  source.subscribeWith({
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
        observer.onSuccess(x);
        subscription.cancel();
      }
    },

    onError: (x: exn) => {
      if (subscribed^ && !finished^) {
        observer.onError(x);
        subscription.cancel();
      }
    }
  })

  subscription;
};