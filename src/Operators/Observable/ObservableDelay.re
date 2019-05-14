
let operator: Utils.trifunc(int, Scheduler.t, ObservableTypes.t({..}, {..}, 'a), ObservableTypes.operator({..}, 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        state#add(scheduler#timeout(() => {
          obs#onComplete();
          state#cancel();
        }, time));
      };

      pub onError = (x) => {
        state#add(scheduler#timeout(() => {
          obs#onError(x);
          state#cancel();
        }, time));
      };

      pub onNext = (x) => {
        state#add(scheduler#timeout(() => {
          obs#onNext(x);
        }, time));
      };
    });
  };
};