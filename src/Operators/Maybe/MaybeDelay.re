
let operator = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onSuccess(x);
        }, time));
      };

      pub onComplete = () => {
        state#link(scheduler#timeout(() => {
          obs#onComplete();
        }, time));
      };

      pub onError = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onError(x);
        }, time));
      };
    });
  };
};