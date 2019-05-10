
let operator: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => state#link(scheduler#run(() => {
        obs#onComplete();
      }));

      pub onError = (x) => state#link(scheduler#run(() => {
        obs#onError(x);
      }));
    })
  };
};