
let operator = (checker, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onSuccess = obs#onSuccess;
        pub onError = (x) => switch (checker(retries^, x)) {
          | true => sub();
          | false => obs#onError(x)
          | exception e => obs#onError(e)
        };
      });
    };

    sub();
  };
};