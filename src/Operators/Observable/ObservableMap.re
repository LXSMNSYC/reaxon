let operator: ('a => 'b) => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'b) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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