/**
 * Runs multiple Single and signals the events of
 * the first one that signals (cancelling the rest).
 * 
 * A subscription to each source will occur in the
 * same order as in this array.
 */
let ambArray: array(SingleTypes.s('source, 'a)) => SingleTypes.operator('downstream, 'a);
/**
 * Runs multiple Single and signals the events of
 * the first one that signals (cancelling the rest).
 * 
 * A subscription to each source will occur in the
 * same order as in this list.
 */
let ambList: list(SingleTypes.s('source, 'a)) => SingleTypes.operator('downstream, 'a);
/**
 * Signals the event of this or the other Single
 * whichever signals first. 
 */
let ambWith: SingleTypes.s('other, 'a) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Stores the success value or exception from the
 * current Single and replays it to late Single.observer.
 * 
 * The returned Single subscribes to the current
 * Single when the first Single.observer subscribes. 
 */
let cache: SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Concatenates an array of Single sources into
 * an Observable
 */
let concatArray: array(SingleTypes.s('source, 'a)) => ObservableTypes.operator('downstream, 'a);
/**
 * Concatenates a list of Single sources into
 * an Observable
 */
let concatList: list(SingleTypes.s('source, 'a)) => ObservableTypes.operator('downstream, 'a);
/**
 * Concatenates a given Single source with this
 * Single source into an Observable.
 */
let concatWith: SingleTypes.s('other, 'a) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a)
/**
 * Signals true if the current Single signals a
 * success value that is equal with the value
 * provided by calling a bi-predicate. 
 */
let contains: 'a => ('a => 'a => bool) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, bool);
/**
 * Calls a supplier for each individual Single.observer
 * to return the actual Single to be subscribed
 * to. 
 */
let defer: (unit => SingleTypes.s('source, 'a)) => SingleTypes.operator('downstream, 'a);
/**
 * Delays the emission of the success signal from
 * the current Single by the specified amount. An
 * error signal will not be delayed. 
 */
let delay: int => Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Delays the actual subscription to the current
 * Single until the given time delay elapsed. 
 */
let delaySubscription: int => Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a)
/**
 * Delays the actual subscription to the current
 * Single until the given time delay elapsed. 
 */
let delayUntil: SingleTypes.s('other, 'a) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Maps the Notification success value of this
 * Single back into normal onSuccess or onError.
 */
let dematerialize: SingleTypes.s('source, Notification.Single.t('a)) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the specified consumer with the success
 * item after this item has been emitted to the
 * downstream.
 */
let doAfterSuccess: ('a => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Registers an action to be called after this
 * Single invokes either onSuccess or onError. 
 */
let doAfterTerminate: (unit => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a)
/**
 * Calls the specified action after this Single
 * signals onSuccess or onError or gets cancelled
 * by the downstream.
 * 
 * In case of a race between a terminal event and
 * a cancel call, the provided onFinally action
 * is executed once per subscription. 
 */
let doFinally: (unit => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the shared action if a Single.observer
 * subscribed to the current Single cancels the
 * common Cancellable it received via onSubscribe. 
 */
let doOnCancel: (unit => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the shared consumer with the error sent
 * via onError for each Single.observer that
 * subscribes to the current Single. 
 */
let doOnError: (exn => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the shared consumer with the error sent
 * via onError or the value via onSuccess for each
 * Single.observer that subscribes to the current
 * Single. 
 */
let doOnEvent: (option('a) => option(exn) => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the shared consumer with the Cancellable
 * sent through the onSubscribe for each Single.observer
 * that subscribes to the current Single. 
 */
let doOnSubscribe: (SingleTypes.subscription => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Calls the shared consumer with the success value
 * sent via onSuccess for each Single.observer that
 * subscribes to the current Single. 
 */
let doOnSuccess: ('a => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Single instance that calls the given
 * onTerminate callback just before this Single
 * completes normally or with an exception. 
 */
let doOnTerminate: (unit => unit) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Compares two Singles and emits true if they
 * emit the same value, compared by a given comparator
 * function. 
 */
let equals: SingleTypes.s('left, 'a) => SingleTypes.s('right, 'b) => ('a => 'b => bool) => SingleTypes.operator('downstream, bool);
/**
 * Returns a Single that invokes a subscriber's
 * onError method when the subscriber subscribes
 * to it. 
 */
let error: exn => SingleTypes.operator('downstream, 'a);
/**
 * Filters the success item of the Single via a
 * predicate function and emitting it if the
 * predicate returns true, completing otherwise. 
 */
let filter: ('a => bool) => SingleTypes.s('source, 'a) => MaybeTypes.operator('downstream, 'a);
/**
 * Returns a Single that is based on applying a
 * specified function to the item emitted by the
 * source Single, where that function returns a
 * Single.  
 */
let flatMap: ('a => SingleTypes.s('result, 'b)) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'b);
/**
 * Returns a Completable that completes based on
 * applying a specified function to the item emitted
 * by the source Single, where that function returns
 * a Completable. 
 */
let flatMapCompletable: ('a => CompletableTypes.s('result)) => SingleTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns a Maybe that is based on applying a specified
 * function to the item emitted by the source Single,
 * where that function returns a Maybe. 
 */
let flatMapMaybe: ('a => MaybeTypes.s('result, 'a)) => SingleTypes.s('source, 'a) => MaybeTypes.operator('downstream, 'a);
/**
 * Returns an Observable that is based on applying a
 * specified function to the item emitted by the source
 * Single, where that function returns an Observable. 
 */
let flatMapObservable: ('a => ObservableTypes.s('result, 'a)) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Maps the success value of the upstream Single into
 * an array and emits its items as an Observable
 * sequence. 
 */
let flattenToArrayObservable: ('a => array('a)) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Maps the success value of the upstream Single into
 * a list and emits its items as an Observable
 * sequence. 
 */
let flattenToListObservable: ('a => list('a)) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals Exceptions.NoSuchElement on completion
 * or error.
 */
let fromCompletable: CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals the given single element or error.
 */
let fromCompletableDefault: 'a => CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals the single element returned by a supplier
 * function or error.
 */
let fromCompletableSupplier: (unit => 'a) => CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps an specific Maybe into a Single and signals
 * its single element or error.
 * 
 * If the Maybe is empty, an Exceptions.NoSuchElement
 * is signalled.
 */
let fromMaybe: MaybeTypes.s('source, 'a) => SingleTypes.operator('downstream ,'a);
/**
 * Wraps an specific Maybe into a Single and signals
 * its single element or the given default element
 * if the source Maybe emits an error signal.
 */
let fromMaybeDefault: 'a => MaybeTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps a specific Observable into a Single and signals
 * its single element or error.
 * 
 * If the Observable is empty, a Exceptions.NoSuchElement
 * is signalled. If the source has more than one element,
 * an Exceptions.IndexOutOfBounds is signalled. 
 */
let fromObservable: ObservableTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
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
let fromSupplier: (unit => 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Hides the identity of the current Single,
 * including the Cancellable that is sent to the
 * downstream via onSubscribe(). 
 */
let hide: SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Completable that ignores the success
 * value of this Single and calls onComplete instead
 * on the returned Completable. 
 */
let ignoreElement: SingleTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns a Single that emits a specified item.
 * 
 * To convert any object into a Single that emits
 * that object, pass that object into the just
 * method. 
 */
let just: 'a => SingleTypes.operator('downstream, 'a);
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
let lift: (SingleTypes.observer('downstream, 'a) => SingleTypes.observer('result, 'b)) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'b);
/**
 * Provides an API (via a cold Single) that bridges
 * the reactive world with the callback-style world. 
 */
let make: (SingleTypes.emitter({
  .
  isCancelled: unit => bool,
  setCancellable: Cancellable.t({..}) => unit,
  onSuccess: 'a => unit,
  onError: exn => unit,
}, 'a) => unit) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Single that applies a specified function
 * to the item emitted by the source Single and emits
 * the result of this function application. 
 */
let map: ('a => 'b) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'b);
/**
 * Maps the signal types of this Single into a Notification
 * of the same kind and emits it as a single success
 * value to downstream.
 */
let materialize: SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, Notification.Single.t('a));
/**
 * Flattens a Single that emits a Single into a single
 * Single that emits the item emitted by the nested Single,
 * without any transformation. 
 */
let merge: SingleTypes.s('source, SingleTypes.s('result, 'a)) => SingleTypes.operator('downstream, 'a);
/**
 * Merges an array of Single sources into an Observable.
 */
let mergeArray: array(SingleTypes.s('source, 'a)) => ObservableTypes.operator('downstream, 'a);
/**
 * Merges a list of Single sources into an Observable.
 */
let mergeList: list(SingleTypes.s('source, 'a)) => ObservableTypes.operator('downstream, 'a);
/**
 * Merges this Single source with a given Single source into
 * an Observable.
 */
let mergeWith: SingleTypes.s('other, 'a) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Returns a singleton instance of a never-signalling
 * Single (only calls onSubscribe). 
 */
let never: unit => SingleTypes.operator('downstream, 'a);
/**
 * Modifies a Single to emit its item (or notify of its
 * error) on a specified Scheduler, asynchronously. 
 */
let observeOn: Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
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
let onErrorResume: (exn => SingleTypes.s('backup, 'a)) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
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
let onErrorResumeNext: SingleTypes.s('backup, 'a) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
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
let onErrorReturn: (exn => 'a) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Signals the specified value as success in case the
 * current Single signals an error. 
 */
let onErrorReturnItem: 'a => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Repeatedly re-subscribes to the current Single and
 * emits each success value. 
 */
let repeat: SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Re-subscribes to the current Single at most the
 * given number of times and emits each success value. 
 */
let repeatCount: int => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Re-subscribes to the current Single until the
 * given predicate returns true. 
 */
let repeatUntil: (int => bool) => SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Repeatedly re-subscribes to the current Single
 * indefinitely if it fails with an onError. 
 */
let retry: SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Repeatedly re-subscribe at most the specified
 * times to the current Single if it fails with an
 * onError. 
 */
let retryCount: int => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Repeatedly re-subscribe to the current Single if
 * the given predicate return false when the Single
 * fails with an onError.
 */
let retryUntil: (int => bool) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Re-subscribe to the current Single if the given
 * predicate returns true when the Single fails with
 * an onError. 
 */
let retryWhile: (int => exn => bool) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Subscribes to a Single and provides callbacks to
 * handle the item it emits or any error notification
 * it issues. 
 */
let subscribe: SingleTypes.recordObserver('a) => SingleTypes.s('source, 'a) => SingleTypes.subscription;
/**
 * Asynchronously subscribes subscribers to this Single
 * on the specified Scheduler.
 */
let subscribeOn: Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Single that emits the item emitted by the
 * source Single until a second Single emits an item.
 * Upon emission of an item from other, this will emit
 * an Exceptions.Cancellation rather than go to
 * Single.observer#onSuccess. 
 */
let takeUntil: SingleTypes.s('other, 'a) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Signals a Exceptions.Timeout if the current Single
 * doesn't signal a success value within the specified
 * timeout window. 
 */
let timeout: int => Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
/**
 * Signals success with 0 value after the given delay
 * for each Single.observer.
 */
let timer: int => Scheduler.t => SingleTypes.operator('downstream, int);
/**
 * Returns a Completable that discards result of the
 * Single and calls onComplete when this source Single
 * calls onSuccess. Error terminal event is propagated. 
 */
let toCompletable: SingleTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Converts this Single into a Maybe.
 */
let toMaybe: SingleTypes.s('source, 'a) => MaybeTypes.operator('downstream, 'a);
/**
 * Converts this Singoe into an Observable.
 */
let toObservable: SingleTypes.s('source, 'a) => ObservableTypes.operator('downstream, 'a);
/**
 * Returns a Single which makes sure when a Single.observer
 * cancels the Cancellable, that call is propagated up
 * on the specified scheduler. 
 */
let unsubscribeOn: Scheduler.t => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'a);
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
let zipWith: SingleTypes.s('other, 'a) => ('a => 'a => 'b) => SingleTypes.s('source, 'a) => SingleTypes.operator('downstream, 'b);