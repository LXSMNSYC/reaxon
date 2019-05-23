
let operator = (sources, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(sources |> List.length);
    let container = Array.make(pending^, None);

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    sources |> List.iteri((index, item) => item#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        Array.set(container, index, Some(x));
        pending := pending^ - 1;

        if (pending^ == 0) {
          switch (combiner(Utils.fromOptionArray(container))) {
            | item => obs#onSuccess(item)
            | exception e => obs#onError(e)
          };
          state#cancel();
        }
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      }
    }));

  };
};