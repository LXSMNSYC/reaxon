
exception CancellationException;


type subscription = Cancellable.Boolean.i;


type observer('observer, 'a);


type t('observer,'a);


type emitter('emitter, 'a);


let ambList: Utils.func(list(t({..}, 'a)), t({..}, 'a));
let ambArray: Utils.func(array(t({..}, 'a)), t({..}, 'a));
let ambWith: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a));

let cache: Utils.func(t({..}, 'a), t({..}, 'a));
let contains: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), t({..}, 'a), t({..}, 'a));

let defer: Utils.func(Utils.supplier(t({..}, 'a)), t({..}, 'a));
let delayUntil: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a));
let doAfterSuccess: Utils.bifunc(Utils.consumer('a), t({..}, 'a), t({..}, 'a));
let doAfterTerminate: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a));
let doFinally: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a));
let doOnCancel: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a));
let doOnError: Utils.bifunc(Utils.consumer(exn), t({..}, 'a), t({..}, 'a));
let doOnEvent: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), t({..}, 'a), t({..}, 'a));
let doOnSubscribe: Utils.bifunc(Utils.consumer(subscription), t({..}, 'a), t({..}, 'a));
let doOnSuccess: Utils.bifunc(Utils.consumer('a), t({..}, 'a), t({..}, 'a));
let doOnTerminate: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a));

let equals: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, bool));
let error: Utils.func(exn, t({..}, 'a));

let flatMap: Utils.bifunc(Utils.func('a, t({..}, 'b)), t({..}, 'a), t({..}, 'b));
let fromsupplier: Utils.func(Utils.supplier('a), t({..}, 'a));

let hide: Utils.func(t({..}, 'a), t({..}, 'a));

let just: Utils.func('a, t({..}, 'a));

let lift: Utils.bifunc(Utils.func(observer({..}, 'a), observer({..}, 'b)), t({..}, 'a), t({..}, 'b));

let make: Utils.func(Utils.consumer(emitter({..}, 'a)), t({..}, 'a));
let map: Utils.bifunc(Utils.func('a, 'b), t({..}, 'a), t({..}, 'b));

let never: Utils.supplier(t({..}, 'a));

let observeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a));
let onErrorResume: Utils.bifunc(Utils.func(exn, t({..}, 'a)), t({..}, 'a), t({..}, 'a));
let onErrorResumeNext: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a));
let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), t({..}, 'a), t({..}, 'a));
let onErrorReturnItem: Utils.bifunc('a, t({..}, 'a), t({..}, 'a));

let retry: Utils.func(t({..}, 'a), t({..}, 'a));
let retryCount: Utils.bifunc(int, t({..}, 'a), t({..}, 'a));
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), t({..}, 'a), t({..}, 'a));

let subscribeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a));

let takeUntil: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a));

let unsubscribeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a));

let zipArray: Utils.bifunc(array(t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b));
let zipList: Utils.bifunc(list(t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b));
let zipWith: Utils.trifunc(t({..}, 'a), Utils.bifunc('a, 'a, 'b), t({..}, 'a), t({..}, 'b));

type basicObserver('a) = {
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
};

let subscribe: Utils.bifunc(basicObserver('a), t({..}, 'a), subscription);