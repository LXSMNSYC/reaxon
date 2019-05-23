
let operator = (sources, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(sources |> Array.length);
    let container = Array.make(pending^, None);

    obs#onSubscribe(Utils.c2sub(state));

    sources |> Array.iteri((index, item) => item#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

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