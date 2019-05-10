
let operator: Utils.bifunc(Utils.func(exn, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (resumeFunction, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

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