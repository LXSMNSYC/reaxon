
let operator: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), MaybeTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = (onEvent, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        onEvent(None, None);
        obs#onComplete();
      };
  
      pub onSuccess = (x) => {
        onEvent(Some(x), None);
        obs#onSuccess(x);
      };
  
      pub onError = (x) => {
        onEvent(None, Some(x));
        obs#onError(x);
      };
    });
  };
};