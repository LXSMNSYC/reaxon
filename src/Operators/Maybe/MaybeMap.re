
let operator: Utils.bifunc(Utils.func('a, 'b), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'b)) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => switch(mapper(x)) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e) 
      };

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    })
  };
};