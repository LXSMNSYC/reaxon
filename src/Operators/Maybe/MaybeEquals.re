
let operator: Utils.trifunc(MaybeTypes.t({..}, {..}, 'a), MaybeTypes.t({..}, {..}, 'b), Utils.option(Utils.bipredicate('a, 'b)), SingleTypes.operator({..}, bool)) = (a, b, comparer) => {
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

      pub onComplete = () => {
        obs#onSuccess(false);
        state#cancel();
      };

      pub onSuccess = (x) => switch(bValue^) {
        | Some(bval) => {
          switch(comparer) {
            | Some(c) => switch(c(x, bval)) {
              | true => obs#onSuccess(true)
              | false => obs#onSuccess(false)
              | exception e => obs#onError(e)
            }
            | None => obs#onSucces(bval == x)
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

      pub onComplete = () => {
        obs#onSuccess(false);
        state#cancel();
      };

      pub onSuccess = (x) => switch(aValue^) {
        | Some(aval) => {
          switch(comparer) {
            | Some(c) => switch(c(aval, x)) {
              | true => obs#onSuccess(true)
              | false => obs#onSuccess(false)
              | exception e => obs#onError(e)
            }
            | None => obs#onSucces(aval == x)
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