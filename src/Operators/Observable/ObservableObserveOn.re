
let operator: Scheduler.t => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => state#add(scheduler#run(() => {
        obs#onSuccess();
      }));

      pub onError = (x) => state#add(scheduler#run(() => {
        obs#onError(x);
      }));

      pub onNext = (x) => state#add(scheduler#run(() => {
        obs#onNext(x);
      }));
    })
  };
};