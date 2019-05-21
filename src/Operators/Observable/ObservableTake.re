let operator: int => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let size = ref(count);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;

      pub onNext = x => if (size^ > 0) {
        size := size^ - 1;

        obs#onNext(x);
      };
    })
  };
};