let operator: int => ObservableTypes.t('source, 'upstream, 'a) => ObservableTypes.operator('downstream, 'a) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let size = ref(count);
    let list = ref([]);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;

      pub onNext = x => if (size^ > 0) {
        size := size^ - 1;
        list := list^ @ [x];
      } else {
        list := list^ @ [x];
        let h = List.hd(list^);
        list := List.tl(list^);

        obs#onNext(h);
      };
    })
  };
};