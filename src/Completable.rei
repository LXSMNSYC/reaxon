/**
 * Returns a Completable which terminates as soon as
 * one of the source Completables terminates (normally
 * or with an error) and cancels all other Completables. 
 */
let ambArray: array(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which terminates as soon as
 * one of the source Completables terminates (normally
 * or with an error) and cancels all other Completables. 
 */
let ambList: list(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that emits the a terminated
 * event of either this Completable or the other
 * Completable whichever fires first. 
 */
let ambWith: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that first runs this Completable
 * and then the other completable. 
 */
let andThen: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Maybe which will subscribe to this Completable
 * and once that is completed then will subscribe to
 * the next MaybeSource. An error event from this
 * Completable will be propagated to the downstream
 * subscriber and will result in skipping the subscription
 * of the Maybe. 
 */
let andThenMaybe: MaybeTypes.s('other, 'a) => CompletableTypes.s('source) => MaybeTypes.operator('downstream, 'a);
/**
 * Returns an Observable which will subscribe to this
 * Completable and once that is completed then will
 * subscribe to the next Observable. An error event
 * from this Completable will be propagated to the
 * downstream subscriber and will result in skipping
 * the subscription of the Observable.
 */
let andThenObservable: ObservableTypes.s('other, 'a) => CompletableTypes.s('source) => ObservableTypes.operator('downstream, 'a);
/**
 * Returns a Single which will subscribe to this
 * Completable and once that is completed then will
 * subscribe to the next SingleSource. An error
 * event from this Completable will be propagated
 * to the downstream subscriber and will result in
 * skipping the subscription of the Single.
 */
let andThenSingle: SingleTypes.s('other, 'a) => CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Subscribes to this Completable only once, when
 * the first Completable.observer subscribes to the
 * result Completable, caches its terminal event
 * and relays/replays it to observers. 
 */
let cache: CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that completes
 * immediately when subscribed to. 
 */
let complete: unit => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which completes only when
 * all sources complete, one after another. 
 */
let concatArray: array(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which completes only when
 * all sources complete, one after another. 
 */
let concatList: list(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Concatenates this Completable with another
 * Completable. 
 */
let concatWith: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Defers the subscription to a Completable instance
 * returned by a supplier. 
 */
let defer: (unit => Types.Completable.t) => Types.Completable.t;
/**
 * Returns a Completable which delays the emission of
 * the completion event by the given time. 
 */
let delay: int => Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that delays the subscription
 * to the source Completable by a given amount
 * of time, both waiting and subscribing on a given
 * Scheduler. 
 */
let delaySubscription: int => Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Maps the signal types of this Completable into a
 * Notification of the same kind and emits it as a
 * single success value to downstream. 
 */
let dematerialize: SingleTypes.s('source, Notification.Completable.t) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that calls the
 * given onTerminate callback after this Completable
 * completes normally or with an exception. 
 */
let doAfterTerminate: (unit => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Calls the specified action after this Completable
 * signals onError or onComplete or gets cancelled by
 * the downstream.
 *
 * In case of a race between a terminal event and a
 * cancel call, the provided onFinally action is
 * executed once per subscription. 
 */
let doFinally: (unit => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Calls the shared action if a Completable.observer
 * subscribed to the current Completable cancels
 * the common Cancellable it received via onSubscribe. 
 */
let doOnCancel: (unit => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which calls the given onComplete
 * callback if this Completable completes. 
 */
let doOnComplete: (unit => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which calls the given onError
 * callback if this Completable emits an error. 
 */
let doOnError: (exn => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which calls the given onEvent
 * callback with the Some(exception) for an onError or
 * None for an onComplete signal from this Completable
 * before delivering said signal to the downstream. 
 */
let doOnEvent: (option(exn) => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that calls the given
 * onSubscribe callback with the Cancellable that child
 * subscribers receive on subscription. 
 */
let doOnSubscribe: (CompletableTypes.subscription => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that calls the given
 * onTerminate callback just before this Completable
 * completes normally or with an exception. 
 */
let doOnTerminate: (unit => unit) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Creates a Completable instance that emits the given
 * exception to subscribers. 
 */
let error: exn => Types.Completable.t;
/**
 * Returns a Completable instance that runs the given
 * action for each subscriber and emits either an unchecked
 * exception or simply completes. 
 */
let fromAction: (unit => unit) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that when subscribed
 * to, subscribes to the Maybe instance and emits a
 * completion event if the maybe emits onSuccess/onComplete
 * or forwards any onError events. 
 */
let fromMaybe: MaybeTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that subscribes to the
 * given Observable, ignores all values and emits only
 * the terminal event. 
 */
let fromObservable: ObservableTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that when subscribed to,
 * subscribes to the Single instance and emits a completion
 * event if the single emits onSuccess or forwards any
 * onError events. 
 */
let fromSingle: SingleTypes.s('source, 'a) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which when subscribed, executes
 * the callable function, ignores its normal result and
 * emits onError or onComplete only. 
 */
let fromSupplier: (unit => 'a) => CompletableTypes.operator('downstream);
/**
 * Hides the identity of this Completable and its
 * Cancellable. 
 */
let hide: CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * This method requires advanced knowledge about
 * building operators, please consider other standard
 * composition methods first; Returns a Completable
 * which, when subscribed to, invokes the provided
 * method for each individual downstream Completable
 * and allows the insertion of a custom operator by
 * accessing the downstream's Completable.observer
 * during this subscription phase and providing a new
 * Completable.observer, containing the custom operator's
 * intended business logic, that will be used in the
 * subscription process going further upstream. 
 */
let lift: (Types.Completable.Observer.t => Types.Completable.Observer.t) => Types.Completable.t => Types.Completable.t;
/**
 * Provides an API (via a cold Completable) that
 * bridges the reactive world with the callback-style
 * world. 
 */
let make: (CompletableTypes.emitter({
  .
  isCancelled: unit => bool,
  setCancellable: Cancellable.t({..}) => unit,
  onComplete: unit => unit,
  onError: exn => unit,
}) => unit) => CompletableTypes.operator('downstream);
/**
 * aps the signal types of this Completable into
 * a Notification of the same kind and emits it
 * as a single success value to downstream. 
 */
let materialize: CompletableTypes.s('source) => SingleTypes.operator('downstream, Notification.Completable.t);
/**
 * Returns a Completable instance that subscribes
 * to all sources at once and completes only when
 * all source Completables complete or one of them
 * emits an error. 
 */
let mergeArray: array(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that subscribes
 * to all sources at once and completes only when
 * all source Completables complete or one of them
 * emits an error. 
 */
let mergeList: list(CompletableTypes.s('source)) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which subscribes to this
 * and the other Completable and completes when
 * both of them complete or one emits an error. 
 */
let mergeWith: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that never calls onError
 * or onComplete. 
 */
let never: unit => CompletableTypes.operator('downstream);
/**
 * Returns a Completable which emits the terminal events
 * from the thread of the specified scheduler. 
 */
let observeOn: Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that if this Completable
 * emits an error, it will emit an onComplete and swallow
 * the exception. 
 */
let onErrorComplete: CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that if this Completable
 * emits an error and the predicate returns true, it
 * will emit an onComplete and swallow the exception. 
 */
let onErrorCompleteWhen: (exn => bool) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that when encounters
 * an error from this Completable, calls the specified
 * mapper function that returns another Completable
 * instance for it and resumes the execution with it. 
 */
let onErrorResume: (exn => CompletableTypes.s('result)) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that when encounters
 * an error from this Completable, resumes the execution
 * with the another Completable. 
 */
let onErrorResumeNext: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that repeatedly subscribes
 * to this Completable until cancelled. 
 */
let repeat: CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that subscribes repeatedly
 * at most the given times to this Completable. 
 */
let repeatCount: int => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that repeatedly subscribes
 * to this Completable so long as the given stop
 * supplier returns false. 
 */
let repeatUntil: (int => bool) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that retries this Completable
 * as long as it emits an onError event. 
 */
let retry: CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that when this Completable
 * emits an error, retries at most the given number
 * of times before giving up and emitting the last
 * error. 
 */
let retryCount: int => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that when this Completable
 * emits an error, retries at most times or until the
 * predicate returns true, whichever happens first
 * and emitting the last error. 
 */
let retryUntil: (int => bool) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that when this Completable
 * emits an error, retries at most times or until the
 * predicate returns false, whichever happens first
 * and emitting the last error. 
 */
let retryWhile: (int => exn => bool) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Subscribes to this Completable and returns a
 * Cancellable which can be used to cancel the
 * subscription. 
 */
let subscribe: CompletableTypes.recordObserver => CompletableTypes.s('source) => CompletableTypes.subscription;
/**
 * Returns a Completable which subscribes the child
 * subscriber on the specified scheduler, making sure
 * the subscription side-effects happen on that specific
 * thread of the scheduler. 
 */
let subscribeOn: Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Terminates the downstream if this or the other
 * Completable terminates (wins the termination race)
 * while cancelling the connection to the losing source. 
 */
let takeUntil: CompletableTypes.s('other) => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable that runs this Completable
 * and emits a Exceptions.Timeout in case this
 * Completable doesn't complete within the given
 * time while "waiting" on the specified Scheduler. 
 */
let timeout: int => Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
/**
 * Returns a Completable instance that fires its
 * onComplete event after the given delay elapsed
 * by using the supplied scheduler. 
 */
let timer: int => Scheduler.t => CompletableTypes.operator('downstream);
/**
 * Converts this Completable into a Maybe.
 */
let toMaybe: CompletableTypes.s('source) => MaybeTypes.operator('downstream, 'a);
/**
 * Returns an Observable which when subscribed
 * to subscribes to this Completable and relays
 * the terminal events to the subscriber.
 */
let toObservable: CompletableTypes.s('source) => ObservableTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals Exceptions.NoSuchElement on completion
 * or error.
 */
let toSingle: CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals the given single element or error.
 */
let toSingleDefault: 'a => CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Wraps an specific Completable into a Single and
 * signals the single element returned by a supplier
 * function or error.
 */
let toSingleSupplier: (unit => 'a) => CompletableTypes.s('source) => SingleTypes.operator('downstream, 'a);
/**
 * Returns a Completable which makes sure when a
 * subscriber cancels the subscription, the cancel
 * is called on the specified scheduler. 
 */
let unsubscribeOn: Scheduler.t => CompletableTypes.s('source) => CompletableTypes.operator('downstream);
