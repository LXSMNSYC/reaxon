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