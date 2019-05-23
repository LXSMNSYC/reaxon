
let operator: ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, bool) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(true);
      pub onNext = () => {
        obs#onSuccess(false);
        state#cancel();
      };
      pub onError = obs#onError;
    })
  };
};