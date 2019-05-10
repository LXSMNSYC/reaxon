
let operator: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        switch(comparer) {
          | Some(cmp) => {
            switch (cmp(x, item)) {
              | result => obs#onSuccess(result)
              | exception e => obs#onError(e);
            };
          }
          | None => obs#onSuccess(x == item)
        };
        state#cancel();
      };

      pub onError = obs#onError;
    })
  };
};