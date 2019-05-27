let operator = (value) => {
  pub subscribeWith = (obs) => {
    let cancelled = ref(false);

    obs#onSubscribe({
      pub cancel = () => {
        cancelled := true;
      };
    });

    if (!cancelled^) {
      obs#onSuccess(value);
      cancelled := true;
    }
  };
};