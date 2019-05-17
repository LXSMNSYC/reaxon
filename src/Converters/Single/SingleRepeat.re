
let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let rec sub = () => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onSuccess = (x) => {
          obs#onNext(x);
          sub();
        };
        pub onError = obs#onError;
      });
    };

    sub();
  };
};