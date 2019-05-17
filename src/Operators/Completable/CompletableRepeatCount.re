
let operator: int => CompletableTypes.t('source) => CompletableTypes.operator('downstream) = (count, source) => {
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

        pub onComplete = () => if (retries^ < count) {
          sub();
        } else {
          obs#onComplete();
        };

        pub onError = obs#onError;
      });
    };

    sub();
  };
};