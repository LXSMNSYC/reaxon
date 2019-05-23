let operator: (Cancellable.t({..}) => unit) => (unit => unit) => ObservableTypes.t('source, 'a) => ObservableTypes.operator('downstream, 'a) = (onSubscribe, onCancel, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            onCancel();
            sub#cancel(); 
          }
        });
      };
  
      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
      pub onNext = obs#onNext;
    });
  };
};