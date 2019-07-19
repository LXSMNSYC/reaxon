let operator: int => Scheduler.t => ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a) = (amount, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe(Utils.c2sub(state));

    let current = ref(None);
    let requestComplete = ref(false);

    let createDebounce = (value) => {
      switch (current^) {
        | Some(item) => item#cancel()
        | None => () 
      };
      let dstate = scheduler#timeout(() => {
        obs#onNext(value);
        current := None;

        if (requestComplete^) {
          obs#onComplete();
          state#cancel();
        }
      }, amount);
      current := Some(dstate);
      state#add(dstate);
    }

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => 
        switch (current^) {
          | Some(dstate) => {
            requestComplete := true;
          }
          | None => {
            obs#onComplete();
            state#cancel();
          }
        };

      pub onError = (e) => {
        obs#onError(e);
        state#cancel();
      };

      pub onNext = createDebounce;
    });
  };
};