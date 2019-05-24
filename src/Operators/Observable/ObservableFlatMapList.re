let operator: list('a) => ('a => ObservableTypes.s('source', 'b)) => ObservableTypes.operator('downstream, 'b) = (sources, mapper) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let size = ref(List.length(sources));

    sources |> List.iter(x =>
      switch (mapper(x)) {
        | source => source#subscribeWith({
          val finished = ref(false);
    
          pub onSubscribe = state#add;
    
          pub onComplete = () =>
            if (!finished^) {
              finished := true;
              size := size^ - 1;
            };
    
          pub onError = e => {
            obs#onError(e);
            state#cancel();
          };
    
          pub onNext = obs#onNext;
        })
        | exception e => {
          obs#onError(e);
          state#cancel();
        }
      }
    );
  };
};