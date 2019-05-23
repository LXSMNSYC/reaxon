
let operator = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    state#add(scheduler#timeout(() => {
      obs#onError(Exceptions.Timeout);
      state#cancel();
    }, time));

    source#subscribeWith({
      pub onSubscribe = state#add;
      
      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };
      
      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};