let operator = (observable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let last = ref(None);
    let single = ref(false);

    observable#subscribeWith({
      pub onSubscribe = state#link;

      pub onNext = (x) => {
        if (single^) {
          obs#onError(Exceptions.IndexOutOfBounds);
          state#cancel();
        } else {
          single := true;
          last := Some(x);
        }
      };

      pub onComplete = () => {
        if (single^) {
          switch (last^) {
            | Some(item) => obs#onSuccess(item)
            | None => obs#onError(Exceptions.NoSuchElement)
          };
        } else {
          obs#onError(Exceptions.NoSuchElement);
        }
      };

      pub onError = obs#onError;
    });
  };
};