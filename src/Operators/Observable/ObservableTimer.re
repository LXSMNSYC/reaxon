
let operator: int => Scheduler.t => ObservableTypes.operator('downstream, int) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onNext(0);
      obs#onComplete();
    }, time));
  }
};
