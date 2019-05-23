let operator: ObservableTypes.t('source, 'a) => MaybeTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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