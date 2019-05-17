
let operator = (a, b, comparer) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let aValue = ref(None);
    let bValue = ref(None);

    a#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => switch(bValue^) {
        | Some(bval) => {
          switch(comparer(x, bval)) {
            | true => obs#onSuccess(true)
            | false => obs#onSuccess(false)
            | exception e => obs#onError(e)
          }
          state#cancel();
        }
        | None => {
          aValue := Some(x);
        }
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    b#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => switch(aValue^) {
        | Some(aval) => {
          switch(comparer(aval, x)) {
            | true => obs#onSuccess(true)
            | false => obs#onSuccess(false)
            | exception e => obs#onError(e)
          }
          state#cancel();
        }
        | None => {
          bValue := Some(x);
        }
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};