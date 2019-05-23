
let operator: Scheduler.t => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    state#link(scheduler#run(() => {
      state#unlink();

      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onComplete = obs#onComplete;
        pub onError = obs#onError;
        pub onNext = obs#onNext;
      });
    }));
  };
};