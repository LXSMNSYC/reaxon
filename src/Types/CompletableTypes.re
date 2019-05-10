type subscription = Cancellable.Boolean.i;


type observer('observer) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
} as 'observer;


type t('t, 'observer) = {
  ..
  subscribeWith: Utils.consumer(observer('observer)),
} as 't;


type emitter('emitter) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.supplier(bool),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
} as 'emitter;

type recordObserver = {
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
};

type defaultObserver('a) = {
  .
  onSubscribe: Utils.consumer(subscription),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
};


type operator('observer) = t({
    .
    subscribeWith: Utils.consumer(observer('observer))
  }, 
  observer('observer),
);
