
let operator: (ObservableTypes.emitter('upstream, 'a) => unit) => ObservableTypes.operator('downstream, 'a) = (onSubscribe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let e = {
      pub setCancellable = state#link;
  
      pub isCancelled = () => state#isCancelled();
    
      pub onComplete = () => if (!state#isCancelled()) {
        obs#onComplete();
        state#cancel();
      };

      pub onNext = (x: 'a) => if (!state#isCancelled()) {
        obs#onNext(x);
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