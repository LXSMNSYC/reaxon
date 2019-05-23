
let operator = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onSuccess(x);
        }, time));
      };

      pub onError = obs#onError;
    });
  };
};