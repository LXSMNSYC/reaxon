
let operator = (sources) => {
  pub subscribeWith = (obs) => {
    let container = Cancellable.Composite.make();
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let winner = ref(None);

    sources |> Array.iter(source => source#subscribeWith({
      val origin = ref(None);

      pub onSubscribe = (c) => {
        origin := Some(c);
        container#add(c);
      };

      pri handler = (callback) => 
        switch (winner^) {
          | Some(w) => if (w == this) {
            callback();
          }
          | None => {
            switch (origin^) {
              | Some(c) => {
                container#remove(c);
                state#link(c);
              } 
              | None => ()
            }
            container#cancel();
            winner := Some(this);
            callback();
          }
        }
      ;

      pub onComplete = () => this#handler(() => obs#onComplete());
      pub onError = x => this#handler(() => obs#onError(x));
      pub onNext = x => this#handler(() => obs#onNext(x));
    }));
  };
};