
let operator: int => Scheduler.t => MaybeTypes.operator('downstream, int) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => obs#onSuccess(0), time));
  }
};
