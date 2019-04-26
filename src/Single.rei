type t('a);
type observer('a);
type emitter('a);

let ambArray: array(t('a)) => t('a);
let ambList: list(t('a)) => t('a);

let contains: 'a => t('a) => t(bool);
let compare: 'a => ('a => 'a => bool) => t('a) => t(bool);
let create: (emitter('a) => unit) => t('a);

let defer: (unit => t('a)) => t('a);
let delayUntil: t('a) => t('a) => t('a);
let doAfterSuccess: ('a => unit) => t('a) => t('a);
let doAfterTerminate: (unit => unit) => t('a) => t('a);
let doFinally: (unit => unit) => t('a) => t('a);
let doOnCancel: (unit => unit) => t('a) => t('a);
let doOnError: (exn => unit) => t('a) => t('a);
let doOnSubscribe: (Cancellable.t => unit) => t('a) => t('a);
let doOnSuccess: ('a => unit) => t('a) => t('a);
let doOnTerminate: (unit => unit) => t('a) => t('a);

let equals: t('a) => t('a) => t(bool);
let exn: exn => t(exn);

let flatMap: ('a => t('a)) => t('a) => t('a);
let fromCallable: (unit => 'a) => t('a);

let just: 'a => t('a);

let map: ('a => 'a) => t('a) => t('a);
let merge: t(t('a)) => t('a);

let never: unit => t('a);

let onErrorResume: (exn => t('a)) => t('a) => t('a);
let onErrorResumeNext: t('a) => t('a) => t('a);
let onErrorReturn: (exn => 'a) => t('a) => t('a);
let onErrorReturnItem: 'a => t('a) => t('a);

let retry: (int => exn => unit) => t('a) => t('a);

let subscribeWith: observer('a) => t('a) => unit;
let subscribe: ('a => unit) => (exn => unit) => t('a) => Cancellable.t;

let takeUntil: t('a) => t('a) => t('a);

let zipArray: array(t('a)) => (array('a) => 'a) => t('a);
let zipList: list(t('a)) => (list('a) => 'a) => t('a);