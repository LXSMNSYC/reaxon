type subscription('subscription) = {
  ..
  request: Utils.consumer(int),
  cancel: Utils.action,
} as 'subscription;

type subscriber('subscriber, 'subscription, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription('subscription)),
  onNext: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
} as 'subscriber;

type publisher('publisher, 'subscriber, 'subscription, 'a) = {
  ..
  subscribe: Utils.consumer(subscriber('subscriber, 'subscription, 'a)),
} as 'publisher;

type processor('processor, 'subscriber, 'subscription, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription('subscription)),
  onNext: Utils.consumer('a),
  onError: Utils.consumer(exn),
  onComplete: Utils.action,
  subscribe: Utils.consumer(subscriber('subscriber, 'subscription, 'a)),
} as 'processor;