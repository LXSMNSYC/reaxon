let operator = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => switch(mapper(x)) {
        | item => {
          item |> Array.iter(i => {
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