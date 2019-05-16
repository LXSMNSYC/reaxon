let operator: int => ObservableTypes.t('source, 'upstream, 'a) => ObservableTypes.operator('downstream, list('a)) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });


    let counter = ref(0);
    let buffer = ref([]);

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => {
        if (counter^ > 0) {
          obs#onNext(buffer^);
        }
        obs#onComplete();
      };
      pub onError = obs#onError;
      pub onNext = (x) => {
        counter := counter^ + 1;
        buffer := buffer^ @ [x];
        if (counter^ >= count) {
          obs#onNext(buffer^);
          counter := 0;
          buffer := [];
        }
      };
    });
  };
};