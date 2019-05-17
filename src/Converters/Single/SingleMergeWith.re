let operator = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let left = ref(false);
    let right = ref(false);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        left := true;
        obs#onNext(x);
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

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        right := true;
        obs#onNext(x);
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