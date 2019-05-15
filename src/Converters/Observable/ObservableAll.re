let operator: ('a => bool) => ObservableTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, bool) = (predicate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => {
        obs#onNext(true);
        obs#onComplete();
      };

      pub onNext = (x) => switch (predicate(x)) {
        | true => () 
        | false => {
          obs#onNext(false);
          obs#onComplete();
          state#cancel();
        }
        | exception e => {
          obs#onError(e)
          state#cancel();
        }
      };

      pub onError = obs#onError;
    });
  };
};