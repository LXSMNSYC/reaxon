let operator: ObservableTypes.t('source, 'a) => MaybeTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let value = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => switch(value^) {
        | Some(x) => obs#onSuccess(x)
        | None => obs#onComplete()
      };
      pub onError = obs#onError;
      pub onNext = x => {
        value := Some(x);
      };
    });
  };
};