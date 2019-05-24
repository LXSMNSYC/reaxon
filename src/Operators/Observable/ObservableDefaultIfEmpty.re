let operator = (item, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let empty = ref(false);

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => {
        if (empty^) {
          obs#onNext(item);
        };
        obs#onComplete();
      };
      pub onNext = (x) => {
        empty := true;
        obs#onNext(x);
      };
      pub onError = obs#onError;
    });
  };
};