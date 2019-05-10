
let operator: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(CompletableTypes.observer({..}))) = ref([]);
  val complete = ref(false);
  val error = ref(None);

  pub subscribeWith = (obs) => {
    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        if (complete^) {
          obs#onComplete();
        } else {
          switch(error^) {
            | Some(e) => obs#onError(e)
            | None => () 
          };
        };
  
        state#cancel();
      }
    } else {
      let state = Cancellable.Boolean.make();

      observers := [obs] @ observers^;

      let subscription = {
        pub isCancelled = state#isCancelled;
        pub cancel = () => {
          observers := observers^ |> List.filter(x => x != obs);
          state#cancel();
        };
      };

      obs#onSubscribe(subscription);

      if (!subscribed^) {
        subscribed := true;
        source#subscribeWith({
          pub onSubscribe = sub => ();
  
          pub onComplete = () => {
            cached := true;
            complete := true;

            observers^ |> List.iter(o => o#onComplete());
            subscription#cancel();
          };

          pub onError = (e) => {
            cached := true;
            error := Some(e);

            observers^ |> List.iter(o => o#onError(e));
            subscription#cancel();
          };
        });
      }
    }
  };
};