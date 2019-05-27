
let operator = (observer: SingleTypes.recordObserver('a), source) => {

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

    pub onSuccess = (x) => 
      if (withSubscription^ && !cancelled^) {
        observer.onSuccess(x)
        subscription#cancel();
      };

    pub onError = (e) => 
      if (withSubscription^ && !cancelled^) {
        observer.onError(e)
        subscription#cancel();
      } else {
        raise(e);
      };
  });

  subscription;
};