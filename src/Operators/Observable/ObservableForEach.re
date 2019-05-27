let operator: ('a => unit) => ObservableTypes.s('source, 'a) => Subscription.s = (onNext, source) => {
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

  source#subscribeWith({
    pub onSubscribe = (state) => 
      if (withSubscription^) {
        state#cancel();
      } else {
        innerState := Some(state);
        withSubscription := true;
      };

    pub onComplete = () => 
      if (!cancelled^) {
        subscription#cancel();
      };

    pub onError = (e) => 
      if (!cancelled^) {
        subscription#cancel();
      } else {
        raise(e);
      };

    pub onNext = (x) => 
      if (!cancelled^) {
        onNext(x);
      };
  });

  subscription;
};