
let operator: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    state#link(scheduler#run(() => {
      state#unlink();

      source#subscribeWith({
        pub onSubscribe = state#link;
  
        pub onComplete = obs#onComplete;

        pub onError = obs#onError;
      });
    }));
  };
};