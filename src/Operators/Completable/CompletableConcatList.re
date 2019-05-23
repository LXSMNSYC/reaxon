
let operator = (completableList)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    if (!state#isCancelled()) {
      let index = ref(0);
      let max = completableList |> List.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          (completableList->List.nth(index^))#subscribeWith({
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