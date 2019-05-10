
let operator: Utils.bifunc(Utils.func('a, SingleTypes.t({..}, {..}, 'b)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        switch(mapper(x)) {
          | item => {
            state#unlink();
            item#subscribeWith({
              pub onSubscribe = state#link;

              pub onSuccess = obs#onSuccess;

              pub onError = obs#onError;
            });
          }
          | exception e => obs#onError(e)
        }
      };

      pub onError = obs#onError;
    });
    
  };
};