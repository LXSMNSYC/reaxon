
let operator: Utils.bifunc(int, Scheduler.t, MaybeTypes.operator({..}, int)) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onSuccess(0);
    }, time));
  }
};
