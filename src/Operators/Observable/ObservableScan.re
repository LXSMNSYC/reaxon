let operator: ('b => 'a => 'b) => option('b) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'b) = (scanner, start, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let current = ref(start);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;

      pub onNext = x => {
        current := switch(current^) {
          | Some(item) => switch (scanner(item, x)) {
            | value => Some(value)
            | exception e => {
              obs#onError(e);
              state#cancel();
              None;
            }
          }
          | None => Some(x)
        };

        switch (current^) {
          | Some(item) => obs#onNext(item)
          | None => ()
        };
      };
    });
  };
};