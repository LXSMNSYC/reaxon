

type subscription = Cancellable.Boolean.i;


type observer('observer) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
} as 'observer;


type t('observer) = {
  .
  subscribeWith: Utils.consumer(observer('observer)),
};


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
