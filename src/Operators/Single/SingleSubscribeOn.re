
let operator: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = (scheduler, source) => {
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
  
        pub onSuccess = obs#onSuccess;

        pub onError = obs#onError;
      });
    }));
  };
};