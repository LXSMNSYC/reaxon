
let operator = (err) => {
  pub subscribeWith = (obs) => {
    let cancelled = ref(false);

    obs#onSubscribe({
      pub cancel = () => {
        cancelled := true;
      };
    });

    if (!cancelled^) {
      obs#onError(err);
      cancelled := true;
    }
  };
};