let operator: ('a => unit) => SingleTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, 'a) = (onSuccess, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        onSuccess(x);
        obs#onSuccess(x);
      };

      pub onError = obs#onError;
    });
  };
};