let operator: (int => bool) => MaybeTypes.t('source, 'a) => MaybeTypes.operator('downstream, 'a) = (supplier, source) => {
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

        pub onSuccess = obs#onSuccess;
        pub onComplete = obs#onComplete;

        pub onError = (x) => switch(supplier(retries^)) {
          | true => obs#onError(x)
          | false => sub()
          | exception e => obs#onError(e)
        };
      });
    };

    sub();
  };
};