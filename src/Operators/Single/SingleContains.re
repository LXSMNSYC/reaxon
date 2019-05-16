
let operator: 'a => option('a => 'a => bool) => SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, bool) = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

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