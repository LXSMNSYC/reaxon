let operator = (supplier, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onComplete = () => switch(supplier(retries^)) {
          | true => obs#onComplete()
          | false => sub()
          | exception e => obs#onError(e)
        };

        pub onSuccess = (x) => {
          obs#onNext(x);
          this#onComplete();
        };
        pub onError = obs#onError;
      });
    };

    sub();
  };
};