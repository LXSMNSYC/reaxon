type t('a);

type observer('a) = {
  onSubscribe: Cancellable.t => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
};

type emitter('a) = {
  observer: ref(observer('a)),
  setCancellable: Cancellable.t => unit,
  cancelled: unit => bool
};