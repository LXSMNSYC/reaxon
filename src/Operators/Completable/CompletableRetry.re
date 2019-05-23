
let operator = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let rec sub = () => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onComplete = obs#onComplete;
        pub onError = (x) => sub();
      });
    };

    sub();
  };
};