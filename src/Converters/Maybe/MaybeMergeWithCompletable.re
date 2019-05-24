let operator: CompletableTypes.s('source) => MaybeTypes.s('sub, 'a) => ObservableTypes.operator('downstream, 'a) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let left = ref(false);
    let right = ref(false);

    let completion = () => if (left^ && right^) {
      obs#onComplete();
      state#cancel();
    };

    let error = e => {
      obs#onError(e);
      state#cancel();
    };

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        left := true;
        completion();
      };

      pub onSuccess = (x) => {
        obs#onNext(x);
        this#onComplete();
      };

      pub onError = error;
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        right := true;
        completion();
      };

      pub onError = error;
    });
  };
};