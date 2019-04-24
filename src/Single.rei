type t('a);

let ambList : list(t('a)) => t('a);
let ambArray: array(t('a)) => t('a);
let ambWith : t('a) => t('a) => t('a);

let cache : t('a) => t('a);
let compose : (t('a) => t('a)) => t('a) => t('a);
let contains: t('a) => t(bool);
let create: (unit => unit) => t('a);

let defer: (unit => t('a)) => t('a);
let doAfterSuccess: ('a => unit) => t('a) => t('a);
let doAfterTerminate: (unit => unit) => t('a) => t('a);
let doFinally: (unit => unit) => t('a) => t('a);
let doOnDispose: (unit => unit) => t('a) => t('a);
let doOnSubscribe: (Cancellable.t => unit) => t('a) => t('a);
let doOnSuccess: ('a => unit) => t('a) => t('a);
let doOnTerminate: (unit => unit) => t('a) => t('a);

let equals: t('a) => t('a) => t(bool);

let takeUntil: t('a) => t('a) => t('a);

let zipArray: array(t('a)) => t('a); 
let zipList: list(t('a)) => t('a);
let zipWith: t('a) => t('a) => t('a);