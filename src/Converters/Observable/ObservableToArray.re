let operator: ObservableTypes.t('source, 'a) => SingleTypes.operator('downstream, array('a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    let array = ref([||]);

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => obs#onSuccess(array^);
      pub onError = obs#onError;
      pub onNext = x => {
        array := Array.concat([array^, [|x|]]);
      };
    });
  };
};