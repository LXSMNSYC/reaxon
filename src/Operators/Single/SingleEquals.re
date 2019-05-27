
let operator = (a, b, comparer) => {
  pub subscribeWith = (obs) => {
    let aState = ref(None);
    let bState = ref(None);

    let aSub = ref(false);
    let bSub = ref(false);

    let cancelled = ref(false);

    let subscription = {
      pub cancel = () => 
        if (!cancelled^) {
          switch (aState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
          switch (bState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
          cancelled := true;
        };
    }

    obs#onSubscribe(subscription);

    let aValue = ref(None);
    let bValue = ref(None);

    a#subscribeWith({
      pub onSubscribe = (state) => {
        if (aSub^) {
          state#cancel();
        } else {
          aState := Some(state);
          aSub := true;
        }
      };

      pub onSuccess = (x) =>
        if (aSub^ && !cancelled^) {
          switch(bValue^) {
          | Some(bval) => {
            switch(comparer(x, bval)) {
              | true => obs#onSuccess(true)
              | false => obs#onSuccess(false)
              | exception e => obs#onError(e)
            }
            subscription#cancel();
          }
          | None => {
            aValue := Some(x);
          }
          switch (aState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
        }
      };

      pub onError = (x) =>
        if (aSub^ && !cancelled^) {
          obs#onError(x);
          subscription#cancel();
        } else {
          raise(x);
        };
    });

    b#subscribeWith({
      pub onSubscribe = (state) => {
        if (bSub^) {
          state#cancel();
        } else {
          bState := Some(state);
          bSub := true;
        }
      };
      pub onSuccess = (x) =>
        if (bSub^ && !cancelled^) {
          switch(aValue^) {
            | Some(aval) => {
              switch(comparer(aval, x)) {
                | true => obs#onSuccess(true)
                | false => obs#onSuccess(false)
                | exception e => obs#onError(e)
              }
              subscription#cancel();
            }
            | None => {
              bValue := Some(x);
            }
          };
          switch (bState^) {
            | Some(sub) => sub#cancel()
            | None => () 
          };
        };

      pub onError = (x) =>
        if (bSub^ && !cancelled^) {
          obs#onError(x);
          subscription#cancel();
        } else {
          raise(x);
        };
    });
  };
};