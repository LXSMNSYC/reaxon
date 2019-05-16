type subscription('subscription) = {
  ..
  request: int => unit,
  cancel: unit => unit,
} as 'subscription;

type subscriber('subscriber, 'subscription, 'a) = {
  ..
  onSubscribe: subscription('subscription) => unit,
  onNext: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
} as 'subscriber;

type publisher('publisher, 'subscriber, 'subscription, 'a) = {
  ..
  subscribe: subscriber('subscriber, 'subscription, 'a) => unit,
} as 'publisher;

type processor('processor, 'subscriber, 'subscription, 'a) = {
  ..
  onSubscribe: subscription('subscription) => unit,
  onNext: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
  subscribe:subscriber('subscriber, 'subscription, 'a) => unit,
} as 'processor;