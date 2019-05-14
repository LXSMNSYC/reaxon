
let operator: Utils.bifunc(Utils.func(exn, bool), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (checker, source) => {
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
        switch (checker(x)) {
          | true => obs#onComplete()
          | false => obs#onError(x)
          | exception e => obs#onError(e)
        };
      };
    });
  };
};