
let operator = (sources)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    if (!state#isCancelled()) {
      let index = ref(0);
      let max = sources |> List.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          (sources->List.nth(index^))#subscribeWith({
            pub onSubscribe = state#link;

            pub onSuccess = x => {
              index := index^ + 1;

              obs#onNext(x);
              if (index^ >= max) {
                obs#onComplete();
              } else {
                sub();
              }
            };

            pub onError = obs#onError;
          }); 
        };

        sub();
      } else {
        obs#onComplete();
        state#cancel();
      }
    }
  };
};