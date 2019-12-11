/**
 * Runs multiple Single and signals the events of
 * the first one that signals (cancelling the rest).
 * 
 * A subscription to each source will occur in the
 * same order as in this array.
 */
let ambArray: array(Types.Single.t('a)) => Types.Single.t('a);
/**
 * Runs multiple Single and signals the events of
 * the first one that signals (cancelling the rest).
 * 
 * A subscription to each source will occur in the
 * same order as in this list.
 */
let ambList: list(Types.Single.t('a)) => Types.Single.t('a);
/**
 * Signals the event of this or the other Single
 * whichever signals first. 
 */
let ambWith: Types.Single.t('a) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Stores the success value or exception from the
 * current Single and replays it to late Single.observer.
 * 
 * The returned Single subscribes to the current
 * Single when the first Single.observer subscribes. 
 */
let cache: Types.Single.t('a) => Types.Single.t('a);
/**
 * Concatenates an array of Single sources into
 * an Observable
 */
let concatArray: array(Types.Single.t('a)) => Types.Observable.t('a);
/**
 * Concatenates a list of Single sources into
 * an Observable
 */
let concatList: list(Types.Single.t('a)) => Types.Observable.t('a);
/**
 * Concatenates a given Single source with this
 * Single source into an Observable.
 */
let concatWith: Types.Single.t('a) => Types.Single.t('a) => Types.Observable.t('a);

let contains: 'a => (('a, 'a) => bool) => Types.Single.t('a) => Types.Single.t(bool);
/**
 * Calls a supplier for each individual Single.observer
 * to return the actual Single to be subscribed
 * to. 
 */
let defer: (unit => Types.Single.t('a)) => Types.Single.t('a);
/**
 * Delays the emission of the success signal from
 * the current Single by the specified amount. An
 * error signal will not be delayed. 
 */
let delay: int => Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Delays the actual subscription to the current
 * Single until the given time delay elapsed. 
 */
let delaySubscription: int => Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Delays the actual subscription to the current
 * Single until the other Single has emitted a
 * success item.
 */
let delayUntil: Types.Single.t('b) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Maps the Notification success value of this
 * Single back into normal onSuccess or onError.
 */
let dematerialize: Types.Single.t(Types.Single.Notification.t('a)) => Types.Single.t('a);
/**
 * Calls the specified consumer with the success
 * item after this item has been emitted to the
 * downstream.
 */
let doAfterSuccess: ('a => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Registers an action to be called after this
 * Single invokes either onSuccess or onError. 
 */
let doAfterTerminate: (unit => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the specified action after this Single
 * signals onSuccess or onError or gets cancelled
 * by the downstream.
 * 
 * In case of a race between a terminal event and
 * a cancel call, the provided onFinally action
 * is executed once per subscription. 
 */
let doFinally: (unit => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the shared action if a Single.observer
 * subscribed to the current Single cancels the
 * common Cancellable it received via onSubscribe. 
 */
let doOnCancel: (unit => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the shared consumer with the error sent
 * via onError for each Single.observer that
 * subscribes to the current Single. 
 */
let doOnError: (exn => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the shared consumer with the error sent
 * via onError or the value via onSuccess for each
 * Single.observer that subscribes to the current
 * Single. 
 */
let doOnEvent: (option('a) => option(exn) => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the shared consumer with the Cancellable
 * sent through the onSubscribe for each Single.observer
 * that subscribes to the current Single. 
 */
let doOnSubscribe: (Types.Subscription.t => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Calls the shared consumer with the success value
 * sent via onSuccess for each Single.observer that
 * subscribes to the current Single. 
 */
let doOnSuccess: ('a => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Returns a Single instance that calls the given
 * onTerminate callback just before this Single
 * completes normally or with an exception. 
 */
let doOnTerminate: (unit => unit) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Returns a Single that invokes a subscriber's
 * onError method when the subscriber subscribes
 * to it. 
 */
let error: exn => Types.Single.t('a);
/**
 * Filters the success item of the Single via a
 * predicate function and emitting it if the
 * predicate returns true, completing otherwise. 
 */
let filter: ('a => bool) => Types.Single.t('a) => Types.Maybe.t('a);
/**
 * Returns a Single that is based on applying a
 * specified function to the item emitted by the
 * source Single, where that function returns a
 * Single.  
 */
let flatMap: ('a => Types.Single.t('b)) => Types.Single.t('a) => Types.Single.t('b);
/**
 * Returns a Completable that completes based on
 * applying a specified function to the item emitted
 * by the source Single, where that function returns
 * a Completable. 
 */
let flatMapCompletable: ('a => Types.Completable.t) => Types.Single.t('a) => Types.Completable.t;
/**
 * Returns a Maybe that is based on applying a specified
 * function to the item emitted by the source Single,
 * where that function returns a Maybe. 
 */
let flatMapMaybe: ('a => Types.Maybe.t('a)) => Types.Single.t('a) => Types.Maybe.t('a);
/**
 * Returns an Observable that is based on applying a
 * specified function to the item emitted by the source
 * Single, where that function returns an Observable. 
 */
let flatMapObservable: ('a => Types.Observable.t('a)) => Types.Single.t('a) => Types.Observable.t('a);
/**
 * Wraps an specific Completable into a Single and
 * signals Exceptions.NoSuchElement on completion
 * or error.
 */
let fromCompletable: Types.Completable.t => Types.Single.t('a);
/**
 * Wraps an specific Completable into a Single and
 * signals the given single element or error.
 */
let fromCompletableDefault: 'a => Types.Completable.t => Types.Single.t('a);
/**
 * Wraps an specific Completable into a Single and
 * signals the single element returned by a supplier
 * function or error.
 */
let fromCompletableSupplier: (unit => 'a) => Types.Completable.t => Types.Single.t('a);
/**
 * Wraps an specific Maybe into a Single and signals
 * its single element or error.
 * 
 * If the Maybe is empty, an Exceptions.NoSuchElement
 * is signalled.
 */
let fromMaybe: Types.Maybe.t('a) => Types.Single.t('a);
/**
 * Wraps an specific Maybe into a Single and signals
 * its single element or the given default element
 * if the source Maybe emits an error signal.
 */
let fromMaybeDefault: 'a => Types.Maybe.t('a) => Types.Single.t('a);
/**
 * Wraps a specific Observable into a Single and signals
 * its single element or error.
 * 
 * If the Observable is empty, a Exceptions.NoSuchElement
 * is signalled. If the source has more than one element,
 * an Exceptions.IndexOutOfBounds is signalled. 
 */
let fromObservable: Types.Observable.t('a) => Types.Single.t('a);
/**
 * Returns a Single that invokes passed function and
 * emits its result for each new Single.observer that
 * subscribes.
 * 
 * Allows you to defer execution of passed function
 * until Single.observer subscribes to the Single.
 * It makes passed function "lazy". Result of the
 * function invocation will be emitted by the Single. 
 */
let fromSupplier: (unit => 'a) => Types.Single.t('a);
/**
 * Hides the identity of the current Single,
 * including the Cancellable that is sent to the
 * downstream via onSubscribe(). 
 */
let hide: Types.Single.t('a) => Types.Single.t('a);
/**
 * Returns a Completable that ignores the success
 * value of this Single and calls onComplete instead
 * on the returned Completable. 
 */
let ignoreElement: Types.Single.t('a) => Types.Completable.t;
/**
 * Returns a Single that emits a specified item.
 * 
 * To convert any object into a Single that emits
 * that object, pass that object into the just
 * method. 
 */
let just: 'a => Types.Single.t('a);
/**
 * This method requires advanced knowledge about
 * building operators, please consider other
 * standard composition methods first;
 * 
 * Returns a Single which, when subscribed to,
 * invokes the provided function for each individual
 * downstream Single and allows the insertion of
 * a custom operator by accessing the downstream's
 * Single.observer during this subscription phase
 * and providing a new Single.observer, containing
 * the custom operator's intended business logic,
 * that will be used in the subscription process
 * going further upstream.
 * 
 * Generally, such a new Single.observer will
 * wrap the downstream's Single.observer and
 * forwards the onSuccess and onError events
 * from the upstream directly or according to
 * the emission pattern the custom operator's
 * business logic requires.
 * 
 * In addition, such operator can intercept the
 * flow control calls of cancel and isCancelled
 * that would have traveled upstream and perform
 * additional actions depending on the same business
 * logic requirements.
 */
let lift: (Types.Single.Observer.t('b) => Types.Single.Observer.t('a)) => Types.Single.t('a) => Types.Single.t('b);
/**
 * Provides an API (via a cold Single) that bridges
 * the reactive world with the callback-style world. 
 */
let make: (Types.Single.Emitter.t('a) => unit) => Types.Single.t('a);
/**
 * Returns a Single that applies a specified function
 * to the item emitted by the source Single and emits
 * the result of this function application. 
 */
let map: ('a => 'b) => Types.Single.t('a) => Types.Single.t('b);
/**
 * Maps the signal types of this Single into a Notification
 * of the same kind and emits it as a single success
 * value to downstream.
 */
let materialize: Types.Single.t('a) => Types.Single.t(Types.Single.Notification.t('a));
/**
 * Flattens a Single that emits a Single into a single
 * Single that emits the item emitted by the nested Single,
 * without any transformation. 
 */
let merge: Types.Single.t(Types.Single.t('a)) => Types.Single.t('a);
/**
 * Merges an array of Single sources into an Observable.
 */
let mergeArray: array(Types.Single.t('a)) => Types.Observable.t('a);
/**
 * Merges a list of Single sources into an Observable.
 */
let mergeList: list(Types.Single.t('a)) => Types.Observable.t('a);
/**
 * Merges this Single source with a given Single source into
 * an Observable.
 */
let mergeWith: Types.Single.t('a) => Types.Single.t('a) => Types.Observable.t('a);
/**
 * Returns a singleton instance of a never-signalling
 * Single (only calls onSubscribe). 
 */
let never: unit => Types.Single.t('a);
/**
 * Modifies a Single to emit its item (or notify of its
 * error) on a specified Scheduler, asynchronously. 
 */
let observeOn: Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Instructs a Single to pass control to another Single
 * rather than invoking Single.observer#onError if it
 * encounters an error.
 * 
 * By default, when a Single encounters an error that
 * prevents it from emitting the expected item to its
 * Single.observer, the Single invokes its Single.observer's
 * onError method, and then quits without invoking any
 * more of its Single.observer's methods. The onErrorResume
 * method changes this behavior. If you pass a function
 * that will return another Single to a Single's onErrorResume
 * method, if the original Single encounters an error,
 * instead of invoking its Single.observer's onError
 * method, it will instead relinquish control to the
 * other Single which will invoke the Single.observer's
 * onSuccess method if it is able to do so. In such a
 * case, because no Single necessarily invokes onError,
 * the Single.observer may never know that an error
 * happened.
 * 
 * You can use this to prevent errors from propagating
 * or to supply fallback data should errors be
 * encountered. 
 */
let onErrorResume: (exn => Types.Single.t('a)) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Instructs a Single to pass control to another Single
 * rather than invoking Single.observer#onError if it
 * encounters an error.
 * 
 * By default, when a Single encounters an error that
 * prevents it from emitting the expected item to its
 * Single.observer, the Single invokes its Single.observer's
 * onError method, and then quits without invoking any
 * more of its Single.observer's methods. The onErrorResume
 * method changes this behavior. If you pass a Single
 * to a Single's onErrorResumeNext method, if the original
 * Single encounters an error, instead of invoking its
 * Single.observer's onError method, it will instead
 * relinquish control to the other Single which will
 * invoke the Single.observer's onSuccess method if it
 * is able to do so. In such a case, because no Single
 * necessarily invokes onError, the Single.observer may
 * never know that an error happened.
 * 
 * You can use this to prevent errors from propagating
 * or to supply fallback data should errors be
 * encountered. 
 */
let onErrorResumeNext: Types.Single.t('a) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Instructs a Single to emit an item (returned by a
 * specified function) rather than invoking onError if
 * it encounters an error.
 * 
 * By default, when a Single encounters an error that
 * prevents it from emitting the expected item to its
 * subscriber, the Single invokes its subscriber's
 * Single.observer#onError method, and then quits
 * without invoking any more of its subscriber's methods.
 * The onErrorReturn method changes this behavior.
 * If you pass a function  to a Single's onErrorReturn
 * method, if the original Single encounters an error,
 * instead of invoking its subscriber's Single.observer#onError
 * method, it will instead emit the return value of
 * the given function.
 * 
 * You can use this to prevent errors from propagating
 * or to supply fallback data should errors be encountered. 
 */
let onErrorReturn: (exn => 'a) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Signals the specified value as success in case the
 * current Single signals an error. 
 */
let onErrorReturnItem: 'a => Types.Single.t('a) => Types.Single.t('a);
/**
 * Repeatedly re-subscribes to the current Single and
 * emits each success value. 
 */
let repeat: Types.Single.t('a) => Types.Observable.t('a);
/**
 * Re-subscribes to the current Single at most the
 * given number of times and emits each success value. 
 */
let repeatCount: int => Types.Single.t('a) => Types.Observable.t('a);
/**
 * Re-subscribes to the current Single until the
 * given predicate returns true. 
 */
let repeatUntil: (int => bool) => Types.Single.t('a) => Types.Observable.t('a);
/**
 * Repeatedly re-subscribes to the current Single
 * indefinitely if it fails with an onError. 
 */
let retry: Types.Single.t('a) => Types.Single.t('a);
/**
 * Repeatedly re-subscribe at most the specified
 * times to the current Single if it fails with an
 * onError. 
 */
let retryCount: int => Types.Single.t('a) => Types.Single.t('a);
/**
 * Repeatedly re-subscribe to the current Single if
 * the given predicate return false when the Single
 * fails with an onError.
 */
let retryUntil: (int => bool) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Re-subscribe to the current Single if the given
 * predicate returns true when the Single fails with
 * an onError. 
 */
let retryWhile: (int => exn => bool) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Subscribes to a Single and provides callbacks to
 * handle the item it emits or any error notification
 * it issues. 
 */
let subscribe: Types.Single.Observer.Lambda.t('a) => Types.Single.t('a) => Types.Subscription.t;
/**
 * Asynchronously subscribes subscribers to this Single
 * on the specified Scheduler.
 */
let subscribeOn: Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Returns a Single that emits the item emitted by the
 * source Single until a second Single emits an item.
 * Upon emission of an item from other, this will emit
 * an Exceptions.Cancellation rather than go to
 * Single.observer#onSuccess. 
 */
let takeUntil: Types.Single.t('a) => Types.Single.t('a) => Types.Single.t('a);
/**
 * Signals a Exceptions.Timeout if the current Single
 * doesn't signal a success value within the specified
 * timeout window. 
 */
let timeout: int => Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Signals success with 0 value after the given delay
 * for each Single.observer.
 */
let timer: int => Types.Scheduler.t => Types.Single.t(int);
/**
 * Returns a Completable that discards result of the
 * Single and calls onComplete when this source Single
 * calls onSuccess. Error terminal event is propagated. 
 */
let toCompletable: Types.Single.t('a) => Types.Completable.t;
/**
 * Converts this Single into a Maybe.
 */
let toMaybe: Types.Single.t('a) => Types.Maybe.t('a);
/**
 * Converts this Singoe into an Observable.
 */
let toObservable: Types.Single.t('a) => Types.Observable.t('a);
/**
 * Returns a Single which makes sure when a Single.observer
 * cancels the Cancellable, that call is propagated up
 * on the specified scheduler. 
 */
let unsubscribeOn: Types.Scheduler.t => Types.Single.t('a) => Types.Single.t('a);
/**
 * Waits until all Single sources provided via an array
 * signal a success value and calls a zipper function
 * with an array of these values to return a result to
 * be emitted to downstream.
 */
let zipArray: array(SingleTypes.s('source, 'a)) => (array('a) => 'b) => SingleTypes.operator('downstream, 'b);
/**
 * Waits until all Single sources provided via an list
 * signal a success value and calls a zipper function
 * with an array of these values to return a result to
 * be emitted to downstream.
 */
let zipList: list(SingleTypes.s('source, 'a)) => (array('a) => 'b) => SingleTypes.operator('downstream, 'b);
/**
 * Returns a Single that emits the result of applying a
 * specified function to the pair of items emitted by the
 * source Single and another specified Single. 
 */
let zipWith: Types.Single.t('a) => ('a => 'a => 'b) => Types.Single.t('a) => Types.Single.t('b);