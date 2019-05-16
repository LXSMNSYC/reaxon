let operator: ObservableTypes.t('source, 'upstream, 'a) => SingleTypes.operator('downstream, array('a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

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