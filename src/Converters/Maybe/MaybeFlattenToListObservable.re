let operator = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;

      pub onSuccess = (x) => switch(mapper(x)) {
        | item => {
          item |> List.iter(i => {
            if (!state#isCancelled()) {
              obs#onNext(i);
            }
          });

          if (!state#isCancelled()) {
            obs#onComplete();
          }
        }
        | exception e => obs#onError(e)
      };

      pub onError = obs#onError;
    });
  };
};