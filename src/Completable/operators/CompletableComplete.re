
let operator: Utils.supplier(CompletableTypes.t({..})) = () => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };  
};