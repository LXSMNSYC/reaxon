
let operator: ObservableTypes.s('other, 'a) => ('a => 'a => 'b) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'b) = (other, combiner, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let left = ref(None);
    let right = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };

      pub onNext = (x) => switch (left^) {
        | Some(value) => 
          switch(combiner(value, x)) {
            | combined => {
              obs#onNext(combined);
            }
            | exception e => this#onError(e);
          }
        | None => {
          right := Some(x);
        }
      };
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };

      pub onNext = (x) => switch (right^) {
        | Some(value) => 
          switch(combiner(x, value)) {
            | combined => {
              obs#onNext(combined);
            }
            | exception e => this#onError(e);
          }
        | None => {
          left := Some(x);
        }
      };
    });
  };
};

