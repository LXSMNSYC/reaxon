
let operator: Utils.bifunc(Scheduler.t, MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => state#link(scheduler#run(obs#onComplete));

      pub onSuccess = (x) => state#link(scheduler#run(() => {
        obs#onSuccess(x);
      }));

      pub onError = (x) => state#link(scheduler#run(() => {
        obs#onError(x);
      }));
    })
  };
};