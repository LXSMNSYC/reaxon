
let operator: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(SingleTypes.observer({..}, 'a))) = ref([]);
  val success = ref(None);
  val error = ref(None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        switch (success^) {
          | Some(x) => obs#onSuccess(x)
          | None => switch(error^) {
            | Some(e) => obs#onError(e)
            | None => () 
          }
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
          pub onSubscribe = (sub) => ();
  
          pub onSuccess = (x) => {
            cached := true;
            success := Some(x);

            observers^ |> List.iter(o => o#onSuccess(x));
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