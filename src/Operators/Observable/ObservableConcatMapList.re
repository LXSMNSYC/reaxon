
let operator: list('a) => ('a => ObservableTypes.s('source, 'b)) => ObservableTypes.operator('downstream, 'b) = (sources, mapper)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    if (!state#isCancelled()) {
      let index = ref(0);
      let max = sources |> List.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          switch (mapper(sources->List.nth(index^))) {
            | item => item#subscribeWith({
              pub onSubscribe = state#link;

              pub onComplete = () => {
                index := index^ + 1;

                if (index^ >= max) {
                  obs#onComplete();
                } else {
                  sub();
                }
              };

              pub onError = obs#onError;
              pub onNext = obs#onNext;
            })
            | exception e => {
              obs#onError(e);
              state#cancel();
            }
          };
        };

        sub();
      } else {
        obs#onComplete();
        state#cancel();
      }
    }
  };
};