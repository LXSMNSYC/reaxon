
let operator = (other, source) => {
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

    other#subscribeWith({
      pub onSubscribe = (state) =>
        if (withSubscription^) {
          state#cancel();
        } else {
          innerState := Some(state);
          withSubscription := true;
        };

      pub onSuccess = (x) => 
        if (withSubscription^ && !cancelled^) {
          switch (innerState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
          innerState := None;
          withSubscription := false;
  
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
                observer#onSuccess(x);
                subscription#cancel();
              };
        
            pub onError = (e) => 
              if (withSubscription^ && !cancelled^) {
                observer#onError(e);
                subscription#cancel();
              } else {
                raise(e);
              };
          });
        };

      pub onError = (e) => 
      if (withSubscription^ && !cancelled^) {
          observer#onError(e);
          subscription#cancel();
        } else {
          raise(e);
        };
    })
  }
};