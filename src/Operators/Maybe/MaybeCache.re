let operator = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(MaybeTypes.observer({..}, 'a))) = ref([]);
  val signal = ref(None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        switch (signal^) {
          | Some(notif) => switch(notif) {
            | Notification.Maybe.OnSuccess(x) => obs#onSuccess(x)
            | Notification.Maybe.OnComplete => obs#onComplete()
            | Notification.Maybe.OnError(x) => obs#onError(x) 
          }
          | None => ()
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

          pub onComplete = () => {
            cached := true;
            signal := Some(OnComplete);

            observers^ |> List.iter(o => o#onComplete());
            subscription#cancel();
          };
  
          pub onSuccess = (x) => {
            cached := true;
            signal := Some(OnSuccess(x));

            observers^ |> List.iter(o => o#onSuccess(x));
            subscription#cancel();
          };

          pub onError = (e) => {
            cached := true;
            signal := Some(OnError(e));

            observers^ |> List.iter(o => o#onError(e));
            subscription#cancel();
          };
        });
      }
    }
  };
};