let operator: Utils.bifunc(Utils.func('a, 'b), ObservableTypes.t({..}, {..}, 'a), ObservableTypes.operator({..}, 'b)) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
      pub onNext = x => switch(mapper(x)) {
        | item => obs#onNext(item)
        | exception e => obs#onError(e) 
      };
    });
  };
};