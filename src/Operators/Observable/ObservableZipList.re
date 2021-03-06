
let operator: list(ObservableTypes.s('source, 'a)) => (array('a) => 'b) => ObservableTypes.operator('downstream, 'b) = (sources, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let length = sources |> List.length;
    let pending = ref(length);
    let container = ref(Array.make(length, None));

    obs#onSubscribe(Utils.c2sub(state));

    sources |> List.iteri((index, item) => item#subscribeWith({
      val emitted = ref(false);

      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };

      pub onNext = (x) => {
        Array.set(container^, index, Some(x));

        if (!emitted^) {
          pending := pending^ - 1;
          emitted := true;
        }

        if (pending^ == 0) {
          switch (combiner(Utils.fromOptionArray(container^))) {
            | item => obs#onNext(item)
            | exception e => this#onError(e)
          };

          container := Array.make(length, None);
          pending := length;
          emitted := false;
        }
      };
    }));

  };
};