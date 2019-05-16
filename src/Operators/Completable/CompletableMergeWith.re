let operator: CompletableTypes.t('other) => CompletableTypes.t('source) => CompletableTypes.operator('downstream) = (other, source) => {
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
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
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