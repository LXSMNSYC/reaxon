
let operator: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#link(scheduler#timeout(() => {
          obs#onComplete();
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