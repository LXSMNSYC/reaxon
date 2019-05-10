
type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
} as 'observer;


type t('t, 'observer,'a) = {
  ..
  subscribeWith: Utils.consumer(observer('observer, 'a)),
} as 't;


type emitter('emitter, 'a) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.supplier(bool),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
} as 'emitter;

type recordObserver('a) = {
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
};

type defaultObserver('a) = {
  .
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
};

type operator('observer, 'a) = t({
    .
    subscribeWith: Utils.consumer(observer('observer, 'a))
  }, 
  observer('observer, 'a),
  'a,
);