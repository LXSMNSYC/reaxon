let operator = (predicate, source) => {
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

      pub onComplete = obs#onComplete;

      pub onError = obs#onError;
    });
  };
};