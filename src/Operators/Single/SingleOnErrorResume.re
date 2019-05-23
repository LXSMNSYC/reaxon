let operator = (resumeIfError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onSuccess = obs#onSuccess;
      pub onError = (x) => switch (resumeIfError(x)) {
        | newSource => {
          state#unlink();
          newSource#subscribeWith({
            pub onSubscribe = state#link;
            pub onSuccess = obs#onSuccess;
            pub onError = obs#onError;
          });
        }
        | exception e => obs#onError(e) 
      };
    });
  };
};