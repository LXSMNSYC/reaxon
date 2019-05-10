
let operator: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, bool)) = (a, b) => {
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

      pub onSuccess = (x) => {
        switch(bValue^) {
          | Some(bval) => {
            obs#onSuccess(bval == x);
            state#cancel();
          }
          | None => {
            aValue := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    b#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch(aValue^) {
          | Some(aval) => {
            obs#onSuccess(aval == x);
            state#cancel();
          }
          | None => {
            bValue := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};