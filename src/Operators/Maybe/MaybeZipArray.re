
let operator = (singleArray, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(singleArray |> Array.length);
    let container = [||];

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    singleArray |> Array.iteri((index, item) => {
      item#subscribeWith({
        pub onSubscribe = state#add;

        pub onComplete = () => {
          obs#onComplete();
          state#cancel();
        };

        pub onSuccess = (x) => {
          Array.set(container, index, x);
          pending := pending^ - 1;

          if (pending^ == 0) {
            switch (combiner(container)) {
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
      })
    });

  };
};