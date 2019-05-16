
let operator: (unit => unit) => SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (onFinally, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            sub#cancel();
            onFinally();
          }
        });
      };
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onFinally();
      };
  
      pub onError  = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
  };
};