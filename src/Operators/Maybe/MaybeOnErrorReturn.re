
let operator: Utils.bifunc(Utils.func(exn, 'a), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (resumeFunction, source) => {
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

      pub onError = (x) => {
        switch (resumeFunction(x)) {
          | item => obs#onSuccess(item)
          | exception e => obs#onError(e)
        };
      };
    });
  };
};