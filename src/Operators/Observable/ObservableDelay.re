
let operator: int => Scheduler.t => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

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