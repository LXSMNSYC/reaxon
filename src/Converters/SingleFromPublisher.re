

let operator: Utils.func(ReactiveStreams.publisher({..}, {..}, {..}, 'a), SingleTypes.t({..}, 'a)) = (publisher) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let last = ref(None);
    let single = ref(false);

    publisher#subscribe({
      pub onSubscribe = (sub) => {
        let subscriptionState = ref(false);
        state#link({
          pub isCancelled = () => subscriptionState^;
          pub cancel = () => {
            subscriptionState := true;
            sub#cancel();
          };
        });

        sub#request(max_int);
      };

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
          state#cancel();
        } else {
          obs#onError(NoSuchElementException);
        }
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};