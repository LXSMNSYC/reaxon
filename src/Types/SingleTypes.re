type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: subscription => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
} as 'observer;


type t('t, 'a) = {
  ..
  subscribeWith: observer({..}, 'a) => unit,
} as 't;

type emitter('emitter, 'a) = {
  ..
  setCancellable: Cancellable.t({..}) => unit,
  isCancelled: unit => bool,
  onSuccess: 'a => unit,
  onError: exn => unit,
} as 'emitter;

type recordObserver('a) = {
  onSuccess: 'a => unit,
  onError: exn => unit,
};

type defaultObserver('a) = {
  .
  onSubscribe: subscription => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
};

type s('s, 'a) = {
  ..
  subscribeWith: defaultObserver('a) => unit
} as 's;

type operator('observer, 'a) = {
  .
  subscribeWith: observer('observer, 'a) => unit
};