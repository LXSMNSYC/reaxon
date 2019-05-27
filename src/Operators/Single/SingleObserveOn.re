
let operator = (scheduler, source) => {
  pub subscribeWith = (observer) => {

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

    observer#onSubscribe(subscription);

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
          scheduler#run(() => 
            if (withSubscription^ && !cancelled^) {
              observer#onSuccess(x);
              subscription#cancel();
            }
          );
        };

      pub onError = (e) => 
        if (withSubscription^ && !cancelled^) {
          scheduler#run(() => 
            if (withSubscription^ && !cancelled^) {
              observer#onError(e);
              subscription#cancel();
            }
          );
        } else {
          raise(e);
        };
    });
  }
};
