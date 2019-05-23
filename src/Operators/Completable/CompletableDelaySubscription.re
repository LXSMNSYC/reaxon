
let operator = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    state#link(scheduler#timeout(() => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onComplete = obs#onComplete;
        pub onError = obs#onError;
      });
    }, time));
  };
};