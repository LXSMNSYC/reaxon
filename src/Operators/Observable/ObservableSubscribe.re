
let operator: ObservableTypes.recordObserver('a) => ObservableTypes.s('source, 'a) => Subscription.s = (obs, source) => {
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
        obs.onComplete()
        subscription#cancel();
      };

    pub onError = (e) => 
      if (!cancelled^) {
        obs.onError(e)
        subscription#cancel();
      } else {
        raise(e);
      };

    pub onNext = (x) => 
      if (!cancelled^) {
        obs.onNext(x)
      };
  });

  subscription;
};