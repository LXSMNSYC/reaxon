let operator: int => ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (index, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let i = ref(0);

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onError(Exceptions.NoSuchElement);
      pub onError = obs#onError;
      pub onNext = x => {
        if (i^ == index) {
          obs#onSuccess(x);
          state#cancel();
        } else if (i^ > index) {
          obs#onError(Exceptions.NoSuchElement);
          state#cancel();
        }
        i := i^ + 1;
      };
    });
  };
};