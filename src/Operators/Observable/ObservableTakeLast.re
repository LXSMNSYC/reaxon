let operator: int => ObservableTypes.t('source, 'a) => ObservableTypes.operator('downstream, 'a) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let size = ref(count);
    let list = ref([]);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        list^ |> List.iter(obs#onNext);
        obs#onComplete()
      };
      pub onError = obs#onError;

      pub onNext = x => if (size^ > 0) {
        size := size^ - 1;
        list := list^ @ [x];
      } else {
        list := list^ @ [x];
        list := List.tl(list^);
      };
    })
  };
};