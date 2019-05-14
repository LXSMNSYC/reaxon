let operator: Utils.bifunc(int, Scheduler.t, CompletableTypes.operator({..})) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(obs#onComplete, time));
  }
};