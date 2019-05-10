
let operator: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (source) => {
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

        pub onSuccess = obs#onSuccess;

        pub onError = (x) => {
          sub();
        };
      });
    };

    sub();
  };
};