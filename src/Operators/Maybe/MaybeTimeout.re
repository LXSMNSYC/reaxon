
let operator: int => Scheduler.t => MaybeTypes.t('source, 'upstream, 'a) => MaybeTypes.operator('downstream, 'a) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let clock = state#add(scheduler#timeout(() => {
      obs#onError(Exceptions.Timeout);
      state#cancel();
    }, time));

    source#subscribeWith({
      pub onSubscribe = state#add;
      
      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };
      
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };
      
      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};