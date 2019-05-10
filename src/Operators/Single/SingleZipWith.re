
let operator: Utils.trifunc(SingleTypes.t({..}, {..}, 'a), Utils.bifunc('a, 'a, 'b), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = (other, combiner, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let left = ref(None);
    let right = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch (left^) {
          | Some(value) => {
            switch(combiner(value, x)) {
              | combined => obs#onSuccess(combined)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
          | None => {
            right := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch (right^) {
          | Some(value) => {
            switch(combiner(value, x)) {
              | combined => obs#onSuccess(combined)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
          | None => {
            left := Some(x);
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