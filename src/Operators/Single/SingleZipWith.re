
let operator = (other, combiner, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let left = ref(None);
    let right = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => switch (left^) {
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

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) =>  switch (right^) {
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

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let operator = (other: Types.Observable.t('a), combiner: ('a, 'a) => 'b, source: Types.Observable.t('a)): Types.Single.t('b) => {
  subscribeWith: (obs: Types.Observable.Observer.t('b)) => {
    let finished = ref(false);

    
  },
};