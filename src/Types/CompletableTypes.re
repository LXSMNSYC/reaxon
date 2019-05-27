type observer('observer) = {
  ..
  onSubscribe: Subscription.t({..}) => unit,
  onComplete: unit => unit,
  onError: exn => unit,
} as 'observer;


type t('t) = {
  ..
  subscribeWith: observer({..}) => unit,
} as 't;


type emitter('emitter) = {
  ..
  setCancellable: Cancellable.t({..}) => unit,
  isCancelled: unit => bool,
  onComplete: unit => unit,
  onError: exn => unit,
} as 'emitter;

type recordObserver = {
  onComplete: unit => unit,
  onError: exn => unit,
};

type defaultObserver('subscription) = {
  .
  onSubscribe: Subscription.t('subscription) => unit,
  onComplete: unit => unit,
  onError: exn => unit,
};

type s('s) = {
  ..
  subscribeWith: defaultObserver({..}) => unit
} as 's;

type operator('observer) = t({
  .
  subscribeWith: observer('observer) => unit
});
