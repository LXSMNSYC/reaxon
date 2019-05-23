let operator: int => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let size = ref(count);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;

      pub onNext = x => if (size^ > 0) {
        size := size^ - 1;
      } else {
        obs#onNext(x);
      };
    })
  };
};