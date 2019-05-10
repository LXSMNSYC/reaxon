
let operator: Utils.trifunc(int, Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onSuccess(x);
        }, time));
      };

      pub onError = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onError(x);
        }, time));
      };
    });
  };
};