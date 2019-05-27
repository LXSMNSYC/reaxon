
let operator = (item, comparer, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = obs#onSubscribe;
      pub onSuccess = x =>
        switch (comparer(x, item)) {
          | result => obs#onSuccess(result)
          | exception e => obs#onError(e)
        };
      pub onError = obs#onError;
    });
};