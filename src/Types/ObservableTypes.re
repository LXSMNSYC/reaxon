
type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onError: Utils.consumer(exn),
  onNext: Utils.consumer('a),
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
  onError: Utils.consumer(exn),
  onNext: Utils.consumer('a),
  onComplete: Utils.action,
} as 'emitter;

type operator('observer, 'a) = t({
    .
    subscribeWith: Utils.consumer(observer('observer, 'a))
  }, 
  observer('observer, 'a),
  'a,
);