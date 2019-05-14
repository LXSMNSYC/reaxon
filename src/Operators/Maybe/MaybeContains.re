
let operator: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), MaybeTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, bool)) = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(false);

      pub onSuccess = (x) => switch(comparer) {
        | Some(cmp) => {
          switch (cmp(x, item)) {
            | result => obs#onSuccess(result)
            | exception e => obs#onError(e);
          };
        }
        | None => obs#onSuccess(x == item)
      };

      pub onError = obs#onError;
    })
  };
};