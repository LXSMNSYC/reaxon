let operator: Utils.bifunc(int, Scheduler.t, CompletableTypes.t({..})) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onComplete();
    }, time));
  }
};