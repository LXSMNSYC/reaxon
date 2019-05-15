let operator: 'a => ObservableTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, 'a) = (default, source) => {
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
        | None => obs#onSuccess(default)
      };
      pub onError = obs#onError;
      pub onNext = x => {
        value := Some(x);
      };
    });
  };
};