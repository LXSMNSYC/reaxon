let operator: int => 'a => ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (index, default, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let i = ref(0);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(default);
      pub onError = obs#onError;
      pub onNext = x => {
        if (i^ == index) {
          obs#onSuccess(x);
          state#cancel();
        } else if (i^ > index) {
          obs#onSuccess(default);
          state#cancel();
        }
        i := i^ + 1;
      };
    });
  };
};