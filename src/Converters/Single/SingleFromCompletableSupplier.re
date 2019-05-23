let operator = (supplier, completable) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    completable#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => switch(supplier()) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e)
      };

      pub onError = obs#onError;
    });
  };
};