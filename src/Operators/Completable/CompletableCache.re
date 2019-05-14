let operator: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(CompletableTypes.observer({..}))) = ref([]);
  val signal: ref(Utils.option(Notification.Completable.t)) = ref(Utils.None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        switch (signal^) {
          | Some(notif) => switch(notif) {
            | Notification.Completable.OnComplete => obs#onComplete()
            | Notification.Completable.OnError(x) => obs#onError(x) 
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