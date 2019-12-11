/**
 * Runs multiple MaybeSources and signals
 * the events of the first one that signals
 * (disposing the rest). 
 */
let ambArray: array(Types.Maybe.t('a)) => Types.Maybe.t('a);
/**
 * Runs multiple MaybeSources and signals
 * the events of the first one that signals
 * (disposing the rest). 
 */
let ambList: list(Types.Maybe.t('a)) => Types.Maybe.t('a);
/**
 * Mirrors the MaybeSource (current or provided)
 * that first signals an event. 
 */
let ambWith: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Returns a Maybe that subscribes to this Maybe
 * lazily, caches its event and replays it, to
 * all the downstream subscribers.
 * 
 * The operator subscribes only when the first
 * downstream subscriber subscribes and maintains
 * a single subscription towards this Maybe. 
 */
let cache: Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Concatenate the single values, in a non-overlapping
 * fashion, of the MaybeSource sources in the array. 
 */
let concatArray: array(Types.Maybe.t('a)) => Types.Observable.t('a);
/**
 * Concatenate the single values, in a non-overlapping
 * fashion, of the MaybeSource sources in the list. 
 */
let concatList: list(Types.Maybe.t('a)) => Types.Observable.t('a);
/**
 * Returns a Flowable that emits the items emitted
 * from the current MaybeSource, then the next,
 * one after the other, without interleaving them. 
 */
let concatWith: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Observable.t('a);
/**
 * Returns a Single that emits a Boolean that
 * indicates whether the source Maybe emitted a
 * specified item. 
 */
let contains: 'a => ('a => 'a => bool) => Types.Maybe.t('a) => Types.Single.t(bool);
/**
 * Returns a Single that counts the total number
 * of items emitted (0 or 1) by the source Maybe
 * and emits this count as a 64-bit Long.
 */
let count: Types.Maybe.t('a) => Types.Single.t(int);
/**
 * Returns a Single that emits the item emitted by
 * the source Maybe or a specified default item if
 * the source Maybe is empty. 
 */
let defaultIfEmpty: 'a => Types.Maybe.t('a) => Types.Single.t('a);
/**
 * Calls a supplier for each individual MaybeObserver
 * to return the actual MaybeSource source to be
 * subscribed to. 
 */
let defer: (unit => Types.Maybe.t('a)) => Types.Maybe.t('a);
/**
 * Returns a Maybe that signals the events emitted
 * by the source Maybe shifted forward in time by
 * a specified delay running on the specified
 * Scheduler. 
 */
let delay: int => Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Returns a Maybe that delays the subscription
 * to the source Maybe by a given amount of time,
 * both waiting and subscribing on a given
 * Scheduler. 
 */
let delaySubscription: int => Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Delays the actual subscription to the current
 * Maybe until the other Maybe has emitted a
 * success item.
 */
let delayUntil: MaybeTypes.s('other, 'a) => MaybeTypes.s('source, 'a) => MaybeTypes.operator('downstream, 'a);
/**
 * Maps the Notification success value of this
 * Maybe back into normal onSuccess, onComplete
 * or onError.
 */
let dematerialize: Types.Single.t(Types.Maybe.Notification.t('a)) => Types.Maybe.t('a);
/**
 * Calls the specified consumer with the success
 * item after this item has been emitted to the
 * downstream. 
 */
let doAfterSuccess: ('a => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Registers an action to be called when this Maybe
 * invokes either onSuccess, onComplete or onError. 
 */
let doAfterTerminate: (unit => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the specified action after this Maybe signals
 * onSuccess, onError or onComplete or gets disposed
 * by the downstream.
 * 
 * In case of a race between a terminal event and a
 * dispose call, the provided onFinally action is
 * executed once per subscription. 
 */
let doFinally: (unit => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the shared Action if a MaybeObserver
 * subscribed to the current Maybe disposes the
 * common Disposable it received via onSubscribe. 
 */
let doOnCancel: (unit => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Modifies the source Maybe so that it invokes an
 * action when it calls onComplete. 
 */
let doOnComplete: (unit => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the shared consumer with the error sent
 * via onError for each MaybeObserver that
 * subscribes to the current Maybe.
 */
let doOnError: (exn => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the given onEvent callback with the
 * (success value, none) for an onSuccess,
 * (none, throwable) for an onError or (null, null)
 * for an onComplete signal from this Maybe
 * before delivering said signal to the downstream. 
 */
let doOnEvent: (option('a) => option(exn) => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the shared consumer with the Disposable
 * sent through the onSubscribe for each MaybeObserver
 * that subscribes to the current Maybe. 
 */
let doOnSubscribe: (Types.Subscription.t => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Calls the shared consumer with the success
 * value sent via onSuccess for each MaybeObserver
 * that subscribes to the current Maybe. 
 */
let doOnSuccess: ('a => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Returns a Maybe instance that calls the given
 * onTerminate callback just before this Maybe
 * completes normally or with an exception. 
 */
let doOnTerminate: (unit => unit) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Returns a (singleton) Maybe instance that
 * calls onComplete immediately. 
 */
let empty: unit => Types.Maybe.t('a);

let equals: MaybeTypes.s('left, 'a) => MaybeTypes.s('right, 'b) => ('a => 'b => bool) => SingleTypes.operator('downstream, bool);
/**
 * Returns a Maybe that invokes a subscriber's
 * onError method when the subscriber subscribes
 * to it. 
 */
let error: exn => Types.Maybe.t('a);
/**
 * Filters the success item of the Maybe via a
 * predicate function and emitting it if the
 * predicate returns true, completing otherwise. 
 */
let filter: ('a => bool) => Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Returns a Maybe that is based on applying a
 * specified function to the item emitted by the
 * source Maybe, where that function returns a
 * MaybeSource. 
 */
let flatMap: ('a => Types.Maybe.t('b)) => Types.Maybe.t('a) => Types.Maybe.t('b);
/**
 * Returns a Completable that completes based on
 * applying a specified function to the item emitted
 * by the source Maybe, where that function returns
 * a Completable. 
 */
let flatMapCompletable: ('a => CompletableTypes.s('result)) => MaybeTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns an Observable that is based on applying a
 * specified function to the item emitted by the source
 * Maybe, where that function returns an ObservableSource. 
 */
let flatMapObservable: ('a => ObservableTypes.s('result, 'a)) => MaybeTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Returns a Single based on applying a specified
 * function to the item emitted by the source Maybe,
 * where that function returns a Single. When this
 * Maybe completes a NoSuchElementException will be
 * thrown. 
 */
let flatMapSingle: ('a => SingleTypes.s('result, 'a)) => MaybeTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Maybe based on applying a specified
 * function to the item emitted by the source Maybe,
 * where that function returns a Single. When this
 * Maybe just completes the resulting Maybe completes
 * as well. 
 */
let flatMapSingleElement: ('a => SingleTypes.s('result, 'a)) => MaybeTypes.s('source, 'a) => MaybeTypes.operator('downstream, 'a);
/**
 * Maps the success value of the upstream Maybe
 * into an array and emits its items as an Observable
 * sequence. 
 */
let flattenToArrayObservable: ('a => array('a)) => MaybeTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Maps the success value of the upstream Maybe
 * into an list and emits its items as an Observable
 * sequence. 
 */
let flattenToListObservable: ('a => list('a)) => MaybeTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Returns a Maybe instance that runs the given
 * Action for each subscriber and emits either
 * its exception or simply completes. 
 */
let fromAction: (unit => unit) => Types.Maybe.t('a);
/**
 * Wraps a CompletableSource into a Maybe.
 */
let fromCompletable: Types.Completable.t => Types.Maybe.t(unit);

let fromObservable: Types.Observable.t('a) => Types.Maybe.t('a);
/**
 * Wraps a SingleSource into a Maybe.
 */
let fromSingle: Types.Single.t('a) => Types.Maybe.t('a);
/**
 * Returns a Maybe that invokes the given supplier
 * for each individual MaybeObserver that subscribes
 * and emits the resulting non-null item via onSuccess
 */
let fromSupplier: (unit => 'a) => Types.Maybe.t('a);
/**
 * Hides the identity of this Maybe and its Disposable. 
 */
let hide: Types.Maybe.t('a) => Types.Maybe.t('a);
/**
 * Ignores the item emitted by the source Maybe and
 * only calls onComplete or onError. 
 */
let ignoreElement: Types.Maybe.t('a) => Types.Completable.t;
/**
 * Returns a Single that emits true if the source
 * Maybe is empty, otherwise false. 
 */
let isEmpty: Types.Maybe.t('a) => Types.Single.t(bool);
/**
 * Returns a Maybe that emits a specified item. 
 */
let just: 'a => Types.Maybe.t('a);
/**
 * This method requires advanced knowledge about
 * building operators, please consider other
 * standard composition methods first; Returns
 * a Maybe which, when subscribed to, invokes
 * the operator for each individual downstream
 * Maybe and allows the insertion of a custom
 * operator by accessing the downstream's MaybeObserver
 * during this subscription phase and providing
 * a new MaybeObserver, containing the custom
 * operator's intended business logic, that will
 * be used in the subscription process going
 * further upstream.
 * 
 * Generally, such a new MaybeObserver will wrap
 * the downstream's MaybeObserver and forwards
 * the onSuccess, onError and onComplete events
 * from the upstream directly or according to the
 * emission pattern the custom operator's business
 * logic requires. In addition, such operator can
 * intercept the flow control calls of dispose and
 * isDisposed that would have traveled upstream and
 * perform additional actions depending on the same
 * business logic requirements. 
 */
let lift: (Types.Maybe.Observer.t('b) => Types.Maybe.Observer.t('a)) => Types.Maybe.t('a) => Types.Maybe.t('b);
/**
 * Provides an API (via a cold Maybe) that bridges
 * the reactive world with the callback-style world. 
 */
let make: (Types.Maybe.Emitter.t('a) => unit) => Types.Maybe.t('a);
/**
 * Returns a Maybe that applies a specified function
 * to the item emitted by the source Maybe and emits
 * the result of this function application. 
 */
let map: ('a => 'b) => Types.Maybe.t('a) => Types.Maybe.t('b);
/**
 * Maps the signal types of this Maybe into a Notification
 * of the same kind and emits it as a single success
 * value to downstream. 
 */
let materialize: Types.Maybe.t('a) => Types.Single.t(Types.Maybe.Notification.t('a));
/**
 * Flattens a MaybeSource that emits a MaybeSource
 * into a single MaybeSource that emits the item
 * emitted by the nested MaybeSource, without any
 * transformation. 
 */
let merge: Types.Maybe.t(Types.Maybe.t('a)) => Types.Maybe.t('a);
/**
 * Merges an array sequence of MaybeSource
 * instances into a single Flowable sequence,
 * running all MaybeSources at once. 
 */
let mergeArray: array(Types.Maybe.t('a)) => Types.Observable.t('a);
/**
 * Merges an list sequence of MaybeSource
 * instances into a single Flowable sequence,
 * running all MaybeSources at once. 
 */
let mergeList: list(Types.Maybe.t('a)) => Types.Observable.t('a);
/**
 * Flattens this and another Maybe into a
 * single Flowable, without any transformation. 
 */
let mergeWith: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Observable.t('a);
/**
 * Returns a Maybe that never sends any items
 * or notifications to a MaybeObserver. 
 */
let never: unit => Types.Maybe.t('a);
let observeOn: Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorComplete: Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorCompleteWhen: (exn => bool) => Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorResume: (exn => Types.Maybe.t('a)) => Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorResumeNext: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorReturn: (exn => 'a) => Types.Maybe.t('a) => Types.Maybe.t('a);
let onErrorReturnItem: 'a => Types.Maybe.t('a) => Types.Maybe.t('a);
let repeat: Types.Maybe.t('a) => Types.Observable.t('a);
let repeatCount: int => Types.Maybe.t('a) => Types.Observable.t('a);
let repeatUntil: (int => bool) => Types.Maybe.t('a) => Types.Observable.t('a);
let retry: Types.Maybe.t('a) => Types.Maybe.t('a);
let retryCount: int => Types.Maybe.t('a) => Types.Maybe.t('a);
let retryUntil: (int => bool) => Types.Maybe.t('a) => Types.Maybe.t('a);
let retryWhile: (int => exn => bool) => Types.Maybe.t('a) => Types.Maybe.t('a);
let subscribe: Types.Maybe.Observer.Lambda.t('a) => Types.Maybe.t('a) => Types.Subscription.t;
let subscribeOn: Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
let switchIfEmpty: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Maybe.t('a);
let switchIfEmptySingle: Types.Single.t('a) => Types.Maybe.t('a) => Types.Single.t('a);
let takeUntil: Types.Maybe.t('a) => Types.Maybe.t('a) => Types.Maybe.t('a);
let timeout: int => Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
let timer: int => Types.Scheduler.t => Types.Maybe.t(int);
let toCompletable: Types.Maybe.t('a) => Types.Completable.t;
let toObservable: Types.Maybe.t('a) => Types.Observable.t('a);
let toSingle: Types.Maybe.t('a) => Types.Single.t('a);
let toSingleDefault: 'a => Types.Maybe.t('a) => Types.Single.t('a);
let unsubscribeOn: Types.Scheduler.t => Types.Maybe.t('a) => Types.Maybe.t('a);
let zipArray: array(MaybeTypes.s('source, 'a)) => (array('a) => 'b) => MaybeTypes.operator('downstream, 'b);
let zipList: list(MaybeTypes.s('source, 'a)) => (array('a) => 'b) => MaybeTypes.operator('downstream, 'b);
let zipWith: Types.Maybe.t('a) => ('a => 'a => 'b) => Types.Maybe.t('a) => Types.Maybe.t('b);