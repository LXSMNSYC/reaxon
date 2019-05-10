
let operator: Utils.func(array(CompletableTypes.t({..})), CompletableTypes.t({..})) = (completableArray)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });
    if (!state#isCancelled()) {
      let index = ref(0);
      let max = completableArray |> Array.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          (completableArray->Array.get(index^))#subscribeWith({
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