let operator: (exn => MaybeTypes.t('backup, 'bstream, 'a)) => MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (resumeIfError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;

      pub onError = (x) => switch (resumeIfError(x)) {
        | newSource => {
          state#unlink();
          newSource#subscribeWith({
            pub onSubscribe = state#link;
            pub onComplete = obs#onComplete;
            pub onSuccess = obs#onSuccess;
            pub onError = obs#onError;
          });
        }
        | exception e => obs#onError(e) 
      };
    });
  };
};