
let operator: (unit => unit) => SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };
  
      pub onError  = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};