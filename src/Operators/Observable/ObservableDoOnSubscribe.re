let operator: (Subscription.t('subscription) => unit) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let innerState = ref(None);
    let cancelled = ref(false);
    let withSubscription = ref(false);

    let subscription = {
      pub cancel = () => 
        if (!cancelled^) {
          switch (innerState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
          cancelled := true;
        }
    };

    obs#onSubscribe(subscription);

    source#subscribeWith({
      pub onSubscribe = (state) => 
        if (withSubscription^) {
          state#cancel();
        } else {
          onSubscribe(state);
          innerState := Some(state);
          withSubscription := true;
        };
  
      pub onComplete = () => 
        if (!cancelled^) {
          obs#onComplete()
          subscription#cancel();
        };
  
      pub onError = (e) => 
        if (!cancelled^) {
          obs#onError(e)
          subscription#cancel();
        } else {
          raise(e);
        };
  
      pub onNext = (x) => 
        if (!cancelled^) {
          obs#onNext(x)
        };
    });
  }
    
};