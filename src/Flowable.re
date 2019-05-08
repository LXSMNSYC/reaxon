type subscription = {
  .
  request: Functions.consumer(int),
  cancel: Functions.action,
};

type subscriber('a) = {
  .
  onSubscribe: Functions.consumer(subscription),
  onNext: Functions.consumer('a),
  onError: Functions.consumer(exn),
  onComplete: Functions.action,
};

type publisher('a) = {
  .
  subscribe: Functions.consumer(subscriber('a)),
};

type emitter('a) = {
  .
  isCancelled: Functions.factory(bool),
  setCleanup: Functions.consumer(Functions.action),
  onNext: Functions.consumer('a),
  onError: Functions.consumer(exn),
  onComplete: Functions.action,
};