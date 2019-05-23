
let operator = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    state#link(scheduler#timeout(() => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;
        pub onSuccess = obs#onSuccess;
        pub onError = obs#onError;
      });
    }, time));
  };
};