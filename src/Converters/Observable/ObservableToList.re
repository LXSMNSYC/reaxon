let operator: ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, list('a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let list = ref([]);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(list^);
      pub onError = obs#onError;
      pub onNext = x => {
        list := list^ @ [x];
      };
    });
  };
};