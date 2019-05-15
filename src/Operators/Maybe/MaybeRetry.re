
let operator: MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (source) => {
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
        pub onComplete = obs#onComplete;
        pub onSuccess = obs#onSuccess;
        pub onError = (x) => sub();
      });
    };

    sub();
  };
};