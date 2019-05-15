
type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: subscription => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
} as 'observer;


type t('t, 'observer,'a) = {
  ..
  subscribeWith: observer('observer, 'a) => unit,
} as 't;


type emitter('emitter, 'a) = {
  ..
  setCancellable: Cancellable.t({..}) => unit,
  isCancelled: unit => bool,
  onSuccess: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
} as 'emitter;

type recordObserver('a) = {
  onSubscribe: subscription => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
};

type defaultObserver('a) = {
  .
  onSubscribe: subscription => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
};

type operator('observer, 'a) = t({
    .
    subscribeWith: observer('observer, 'a) => unit
  }, 
  observer('observer, 'a),
  'a,
);