
let operator = (completableArray) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    completableArray |> Array.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};