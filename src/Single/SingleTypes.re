type subscription = Cancellable.Boolean.i;

type observer('observer, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'observer;


type t('observer,'a) = {
  .
  subscribeWith: Utils.consumer(observer('observer, 'a)),
};


type emitter('emitter, 'a) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.supplier(bool),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'emitter;

type recordObserver('a) = {
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
};
