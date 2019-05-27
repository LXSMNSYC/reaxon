
let operator = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let innerState = ref(None);
    let cancelled = ref(false);
    let withSub = ref(false);

    let subscription = {
      pub cancel = () =>
        if (!cancelled^) {
          switch (innerState^) {
            | Some(sub) => sub#cancel()
            | None => ()
          };
          cancelled := true;
        };
    }

    obs#onSubscribe(subscription);

    source#subscribeWith({
      pub onSubscribe = (state) =>
        if (withSub^) {
          state#cancel();
        } else {
          innerState := Some(state);
          withSub := true;
        };

      pub onSuccess = (x) =>
        if (withSub^ && !cancelled^) {
          switch(mapper(x)) {
            | item => {
              let subCall = () => {
                item#subscribeWith({
                  pub onSubscribe = (state) =>
                    if (withSub^) {
                      state#cancel();
                    } else {
                      innerState := Some(state);
                      withSub := true;
                    };
                  pub onSuccess =  (x) =>
                    if (withSub^ && !cancelled^) {
                      obs#onSuccess(x);
                      subscription#cancel();
                    };
  
                  pub onError = (x) =>
                    if (withSub^ && !cancelled^) {
                      obs#onError(x);
                      subscription#cancel();
                    } else {
                      raise(x);
                    };
                });
              };
              switch (innerState^) {
                | Some(sub) => {
                  innerState := None;
                  subCall();
                  sub#cancel();
                }
                | None => subCall()
              };
              
            }
            | exception e => {
              obs#onError(x);
              subscription#cancel();
            }
          };
        };

      pub onError = (x) =>
        if (withSub^ && !cancelled^) {
          obs#onError(x);
          subscription#cancel();
        } else {
          raise(x);
        };
    });
    
  };
};