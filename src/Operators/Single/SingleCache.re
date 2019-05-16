let operator: SingleTypes.t('source, 'a) => SingleTypes.operator('downstream, 'a) = (source) => {
  val cached = ref(false);
  val subscribed = ref(false);
  val observers = ref([]);
  val signal = ref(None);

  pub subscribeWith = (obs) => {
    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        switch (signal^) {
          | Some(notif) => switch(notif) {
            | Notification.Single.OnSuccess(x) => obs#onSuccess(x)
            | Notification.Single.OnError(x) => obs#onError(x) 
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