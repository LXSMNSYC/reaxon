
let operator: Utils.trifunc(int, Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let clock = state#add(scheduler#timeout(() => {
      obs#onError(Exceptions.Timeout);
      state#cancel();
    }, time));

    source#subscribeWith({
      pub onSubscribe = state#add;
      
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };
      
      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};