
let instance = {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };  
};

let operator: unit => ObservableTypes.operator('downstream, 'a) = () => instance;