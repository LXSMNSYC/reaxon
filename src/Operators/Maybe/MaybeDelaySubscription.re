
let operator: Utils.trifunc(int, Scheduler.t, MaybeTypes.t({..}, 'a), CompletableTypes.t({..}, 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    state#link(scheduler#timeout(() => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onSuccess = obs#onSuccess;
        pub onComplete = obs#onComplete;
        pub onError = obs#onError;
      });
    }, time));
  };
};