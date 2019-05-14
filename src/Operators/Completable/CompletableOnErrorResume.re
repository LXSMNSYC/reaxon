let operator: Utils.bifunc(Utils.func(exn, CompletableTypes.t({..}, {..})), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (resumeIfError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;

      pub onError = (x) => switch (resumeIfError(x)) {
          | newSource => {
            state#unlink();
            newSource#subscribeWith({
              pub onSubscribe = state#link;
              pub onComplete = obs#onComplete;
              pub onError = obs#onError;
            });
          }
          | exception e => obs#onError(e) 
        };
    });
  };
};