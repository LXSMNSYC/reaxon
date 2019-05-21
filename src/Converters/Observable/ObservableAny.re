let operator: ('a => bool) => ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, bool) = (predicate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        obs#onNext(false);
        obs#onComplete();
      };

      pub onNext = (x) => switch (predicate(x)) {
        | true => {
          obs#onNext(true);
          obs#onComplete();
          state#cancel();
        }
        | false => () 
        | exception e => {
          obs#onError(e)
          state#cancel();
        }
      };

      pub onError = obs#onError;
    });
  };
};