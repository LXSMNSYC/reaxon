let operator: int => Scheduler.t => CompletableTypes.operator('downstream) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(obs#onComplete, time));
  }
};