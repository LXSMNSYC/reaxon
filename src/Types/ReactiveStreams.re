type subscription('subscription) = {
  ..
  request: int => unit,
  cancel: unit => unit,
} as 'subscription;

type subscriber('subscriber, 'a) = {
  ..
  onSubscribe: subscription({..}) => unit,
  onNext: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
} as 'subscriber;

type publisher('publisher, 'a) = {
  ..
  subscribe: subscriber({..}, 'a) => unit,
} as 'publisher;

type processor('processor,'a) = {
  ..
  onSubscribe: subscription({..}) => unit,
  onNext: 'a => unit,
  onError: exn => unit,
  onComplete: unit => unit,
  subscribe: subscriber({..}, 'a) => unit,
} as 'processor;