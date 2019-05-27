
let operator = (mapper, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;

      pub onSuccess = (x) =>
        switch(mapper(x)) {
          | item => obs#onSuccess(item)
          | exception e => obs#onError(e) 
        };

      pub onError = obs#onError;
    });
};