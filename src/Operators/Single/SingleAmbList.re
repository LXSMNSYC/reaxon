let operator: Utils.func(list(SingleTypes.t({..}, {..}, 'a)), SingleTypes.operator({..}, 'a)) = (singleList) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

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