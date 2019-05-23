
let operator = (onSubscribe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let e = {
      pub setCancellable = state#link;
  
      pub isCancelled = state#isCancelled;

      pub onComplete = () => if (!state#isCancelled()) {
        obs#onComplete();
        state#cancel();
      };
    
      pub onSuccess = (x: 'a) => if (!state#isCancelled()) {
        obs#onSuccess(x);
        state#cancel();
      };
  
      pub onError = (x: exn) => if (!state#isCancelled()) {
        obs#onError(x);
        state#cancel();
      };
    };

    try(onSubscribe(e)) {
      | err => e#onError(err)
    };
  };
};