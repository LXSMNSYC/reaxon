
type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onError: Utils.consumer(exn),
  onNext: Utils.consumer('a),
  onComplete: Utils.action,
} as 'observer;


type t('observer,'a) = {
  .
  subscribeWith: Utils.consumer(observer('observer, 'a)),
};


type emitter('emitter, 'a) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.supplier(bool),
  onError: Utils.consumer(exn),
  onNext: Utils.consumer('a),
  onComplete: Utils.action,
} as 'emitter;