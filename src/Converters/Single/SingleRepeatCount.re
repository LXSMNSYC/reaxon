
let operator = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onSuccess = (x) => {
          obs#onNext(x);
          if (retries^ < count) {
            sub();
          } else {
            obs#onComplete();
          }
        };

        pub onError = obs#onError;
      });
    };

    sub();
  };
};