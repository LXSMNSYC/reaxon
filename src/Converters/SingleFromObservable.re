let operator: Utils.func(Observable.t({..}, 'a), SingleTypes.t({..}, 'a)) = (observable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    observer#subscribeWith({
      pub onSubscribe = (sub) => state#link;

      pub onNext = (x) => {
        if (single^) {
          obs#onError(IndexOutOfBoundsException);
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
            | None => obs#onError(NoSuchElementException)
          };
        } else {
          obs#onError(NoSuchElementException);
        }
      };

      pub onError = obs#onError;
    });
  };
};