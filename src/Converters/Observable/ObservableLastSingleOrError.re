let operator: ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let value = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => switch(value^) {
        | Some(x) => obs#onSuccess(x)
        | None => obs#onError(Exceptions.NoSuchElement)
      };
      pub onError = obs#onError;
      pub onNext = x => {
        value := Some(x);
      };
    });
  };
};