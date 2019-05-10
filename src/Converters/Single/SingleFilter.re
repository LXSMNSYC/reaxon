let operator: Utils.bifunc(Utils.predicate('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), MaybeTypes.t({..}, 'a)) = (predicate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = x => switch(predicate(x)) {
        | true => obs#onSuccess(x)
        | false => obs#onComplete()
        | exception e => obs#onError(e) 
      };

      pub onError = obs#onError;
    });
  };
};