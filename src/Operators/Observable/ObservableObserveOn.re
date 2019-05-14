
let operator: Utils.bifunc(Scheduler.t, ObservableTypes.t({..}, {..}, 'a), ObservableTypes.operator({..}, 'a)) = (scheduler, source) => {
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