let operator: Utils.bifunc(Utils.bipredicate(int, exn), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (checker, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onComplete = obs#onComplete;

        pub onError = (x) => if (checker(retries^, x)) {
          sub();
        } else {
          obs#onError(x);
        };
      });
    };

    sub();
  };
};