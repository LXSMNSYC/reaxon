type subscription = {
  .
  request: Utils.consumer(int),
  cancel: Utils.action,
};

type subscriber('a) = {
  .
  onSubscribe: Utils.consumer(subscription),
  onNext: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
};

type publisher('a) = {
  .
  subscribe: Utils.consumer(subscriber('a)),
};

type emitter('a) = {
  .
  isCancelled: Utils.factory(bool),
  setCleanup: Utils.consumer(Utils.action),
  onNext: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
};