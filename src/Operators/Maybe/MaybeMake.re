let operator = (onSubscribe: Types.Maybe.Emitter.t('a) => unit): Types.Maybe.t('a) => {
  subscribeWith: (obs: Types.Maybe.Observer.t('a)) => {
    let subscribed = ref(false);
    let finished = ref(false);
    let subRef: ref(option(Types.Subscription.t)) = ref(None);
  
    let cancelRef = () => {
      if (subscribed^) {
        switch (subRef^) {
          | Some(ref) => ref.cancel()
          | None => ()
        }
      }
    };
    
    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!finished^) {
          cancelRef();
          finished := true;
        }
      }
    };

    let emitter: Types.Maybe.Emitter.t('a) = {
      setSubscription: (sub: Types.Subscription.t) => {
        if (!finished^) {
          cancelRef();
          subscribed := true;
          subRef := Some(sub);
        } else {
          sub.cancel();
        }
      },
      isCancelled: () => finished^,
      onComplete: () => {
        if (subscribed^ && !finished^) {
          obs.onComplete();
          subscription.cancel();
        }
      },
      onSuccess: (x: 'a) => {
        if (subscribed^ && !finished^) {
          obs.onSuccess(x);
          subscription.cancel();
        }
      },
      onError: (x: exn) => {
        if (subscribed^ && !finished^) {
          obs.onError(x);
          subscription.cancel();
        }
      },
    };

    try (onSubscribe(emitter)) {
      | e => emitter.onError(e)
    }
  }
};