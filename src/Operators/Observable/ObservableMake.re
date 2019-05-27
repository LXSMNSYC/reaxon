let operator: (ObservableTypes.emitter('upstream, 'a) => unit) => ObservableTypes.operator('downstream, 'a) = (onSubscribe) => {
  pub subscribeWith = (obs) => {
    let cancelled = ref(false);
    let callbacks = ref([]);
    let subscription = {
      pub cancel = () => 
        if (!cancelled^) {
          callbacks^ |> List.iter(x => x());
          cancelled := true;
        };
    }

    obs#onSubscribe(subscription);

    let e = {
      pub addCleanup = (callback) =>
        if (!cancelled^) {
          callbacks := callbacks^ @ [callback];
        };
  
      pub isCancelled = () => cancelled^;

      pub onComplete = () =>
        if (!cancelled^) {
          obs#onComplete();
          subscription#cancel();
        };

      pub onError = (x: exn) =>
        if (!cancelled^) {
          obs#onError(x);
          subscription#cancel();
        };
    
      pub onNext = (x: 'a) =>
        if (!cancelled^) {
          obs#onSuccess(x);
        };
    };

    try(onSubscribe(e)) {
      | err => e#onError(err)
    };
  };
};