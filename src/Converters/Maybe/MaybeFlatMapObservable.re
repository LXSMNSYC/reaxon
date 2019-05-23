let operator = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;

      pub onSuccess = (x) => {
        switch(mapper(x)) {
          | item => {
            state#unlink();
            item#subscribeWith({
              pub onSubscribe = state#link;
              pub onNext = obs#onNext;
              pub onComplete = obs#onComplete;
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