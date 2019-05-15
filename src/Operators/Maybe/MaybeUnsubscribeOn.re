
let operator: Scheduler.t => MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (scheduler, source) => {
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