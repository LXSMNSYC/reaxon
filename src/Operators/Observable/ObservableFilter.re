let operator: ('a => bool) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (filter, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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