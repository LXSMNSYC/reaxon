
let operator: (SingleTypes.emitter('upstream, 'a) => unit) => SingleTypes.operator('downstream, 'a) = (onSubscribe) => {
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
    
      pub onSuccess = (x: 'a) =>
        if (!cancelled^) {
          obs#onSuccess(x);
          subscription#cancel();
        };
  
      pub onError = (x: exn) =>
        if (!cancelled^) {
          obs#onError(x);
          subscription#cancel();
        };
    };

    try(onSubscribe(e)) {
      | err => e#onError(err)
    };
  };
};