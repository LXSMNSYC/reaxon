
let operator = (checker, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = obs#onComplete;
      pub onSuccess = obs#onSuccess;

      pub onError = (x) => switch (checker(x)) {
        | true => obs#onComplete()
        | false => obs#onError(x)
        | exception e => obs#onError(e)
      };
    });
  };
};