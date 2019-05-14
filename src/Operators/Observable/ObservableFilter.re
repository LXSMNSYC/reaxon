let operator: Utils.bifunc(Utils.predicate('a), ObservableTypes.t({..}, {..}, 'a), ObservableTypes.operator({..}, 'a)) = (filter, source) => {
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
      pub onNext = x => switch(filter(x)) {
        | true => obs#onNext(x)
        | false => ()
        | exception e => obs#onError(e) 
      };
    });
  };
};