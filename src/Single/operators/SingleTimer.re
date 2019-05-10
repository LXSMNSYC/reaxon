
let operator: Utils.bifunc(int, Scheduler.t, SingleTypes.t({..}, 'a)) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onSuccess(0);
    }, time));
  }
};
