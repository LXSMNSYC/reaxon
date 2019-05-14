
let operator: Utils.bifunc(Scheduler.t, MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = () => {
        scheduler#run(state#cancel);
        ();
      };
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
  };
};