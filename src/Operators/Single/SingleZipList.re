
let operator: Utils.bifunc(list(SingleTypes.t({..}, 'a)), Utils.func(array('a), 'b), SingleTypes.t({..}, 'b)) = (singleList, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(singleList |> List.length);
    let container = [||];

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let index = ref(0);

    singleList |> List.iter(item => {
      item#subscribeWith({
        pub onSubscribe = state#add;

        pub onSuccess = (x) => {
          Array.set(container, index^, x);
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