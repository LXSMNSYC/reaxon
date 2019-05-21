
let operator: Scheduler.t => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

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