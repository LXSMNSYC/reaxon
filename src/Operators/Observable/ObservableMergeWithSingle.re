let operator: SingleTypes.s('other, 'a) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let left = ref(false);
    let right = ref(false);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        left := true;

        if (left^ && right^) {
          obs#onComplete();
          state#cancel();
        }
      };

      pub onError = e => {
        obs#onError(e);
        state#cancel();
      };

      pub onNext = obs#onNext;
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onNext(x);
        right := true;

        if (left^ && right^) {
          obs#onComplete();
          state#cancel();
        }
      };

      pub onError = e => {
        obs#onError(e);
        state#cancel();
      };
    });
  };
};