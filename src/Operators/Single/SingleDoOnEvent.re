
let operator: (option('a) => option(exn) => unit) => SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (onEvent, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        onEvent(Some(x), None);
        obs#onSuccess(x);
      };
  
      pub onError = (x) => {
        onEvent(None, Some(x));
        obs#onError(x);
      };
    });
  };
};