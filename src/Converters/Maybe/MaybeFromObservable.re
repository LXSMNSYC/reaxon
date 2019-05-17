let operator = (observable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

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
            | None => obs#onComplete()
          };
        } else {
          obs#onComplete();
        }
      };

      pub onError = obs#onError;
    });
  };
};