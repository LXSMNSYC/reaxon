let operator: ('b => 'a => 'b) => option('b) => ObservableTypes.t('source, 'a) => MaybeTypes.operator('downstream, 'b) = (reducer, start, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let current = ref(start);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => switch(current^){
        | Some(item) => obs#onSuccess(item)
        | None => obs#onComplete()
      };

      pub onError = obs#onError;

      pub onNext = x => {
        current := switch(current^) {
          | Some(item) => switch (reducer(item, x)) {
            | value => Some(value)
            | exception e => {
              obs#onError(e);
              state#cancel();
              None;
            }
          }
          | None => Some(x)
        };
      };
    });
  };
};