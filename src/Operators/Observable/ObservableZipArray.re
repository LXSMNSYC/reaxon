
let operator: array(ObservableTypes.s('source, 'a)) => (array(option('a)) => 'b) => ObservableTypes.operator('downstream, 'b) = (sources, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let length = sources |> Array.length
    let pending = ref(length);
    let container = ref(Array.make(length, None));

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });


    sources |> Array.iteri((index, item) => item#subscribeWith({
      val emitted = ref(false);

      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onNext = (x) => {
        Array.set(container^, index, Some(x));

        if (!emitted^) {
          pending := pending^ - 1;
          emitted := true;
        }

        if (pending^ == 0) {
          switch (combiner(container^)) {
            | item => obs#onNext(item)
            | exception e => obs#onError(e)
          };

          container := Array.make(length, None);
          pending := length;
          emitted := false;
        }
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      }
    }));

  };
};