let operator = (singleList) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    singleList |> List.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};