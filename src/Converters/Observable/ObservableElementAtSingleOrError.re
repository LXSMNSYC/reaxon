let operator: int => ObservableTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, 'a) = (index, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

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