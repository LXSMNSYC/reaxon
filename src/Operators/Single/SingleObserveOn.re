
let operator = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => state#link(scheduler#run(() => {
        obs#onSuccess(x);
      }));

      pub onError = (x) => state#link(scheduler#run(() => {
        obs#onError(x);
      }));
    })
  };
};