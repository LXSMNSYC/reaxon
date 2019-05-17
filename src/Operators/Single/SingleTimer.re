
let operator = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => obs#onSuccess(0), time));
  }
};
