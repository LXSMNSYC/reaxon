let ambArray = CompletableAmbArray.operator;
let ambList = CompletableAmbList.operator;
let ambWith = CompletableAmbWith.operator;
let andThen = CompletableConcatWith.operator;
let andThenMaybe = CompletableAndThenMaybe.operator;
let andThenObservable = CompletableAndThenObservable.operator;
let andThenSingle = CompletableAndThenSingle.operator;

let cache = CompletableCache.operator;
let complete = CompletableComplete.operator;
let concatArray = CompletableConcatArray.operator;
let concatList = CompletableConcatList.operator;
let concatWith = CompletableConcatWith.operator;

let defer = CompletableDefer.operator;
let delay = CompletableDelay.operator;
let delaySubscription = CompletableDelaySubscription.operator;
let dematerialize = CompletableDematerialize.operator;
let doAfterTerminate = CompletableDoAfterTerminate.operator;
let doFinally = CompletableDoFinally.operator;
let doOnCancel = CompletableDoOnCancel.operator;
let doOnComplete = CompletableDoOnComplete.operator;
let doOnError = CompletableDoOnError.operator;
let doOnEvent = CompletableDoOnEvent.operator;
let doOnSubscribe = CompletableDoOnSubscribe.operator;
let doOnTerminate = CompletableDoOnTerminate.operator;

let error = CompletableError.operator;

let fromAction = CompletableFromAction.operator;
let fromMaybe = CompletableFromMaybe.operator;
let fromObservable = CompletableFromObservable.operator;
let fromSingle = CompletableFromSingle.operator;
let fromSupplier = CompletableFromSupplier.operator;

let hide = CompletableHide.operator;

let lift = CompletableLift.operator;

let make = CompletableMake.operator;
let materialize = CompletableMaterialize.operator;
let mergeArray = CompletableMergeArray.operator;
let mergeList = CompletableMergeList.operator;
let mergeWith = CompletableMergeWith.operator;

let never = CompletableNever.operator;

let observeOn = CompletableObserveOn.operator;
let onErrorComplete = CompletableOnErrorComplete.operator;
let onErrorCompleteWhen = CompletableOnErrorCompleteWhen.operator;
let onErrorResume = CompletableOnErrorResume.operator;
let onErrorResumeNext = CompletableOnErrorResumeNext.operator;

let repeat = CompletableRepeat.operator;
let repeatCount = CompletableRepeatCount.operator;
let repeatUntil = CompletableRepeatUntil.operator;
let retry = CompletableRetry.operator;
let retryCount = CompletableRetryCount.operator;
let retryUntil = CompletableRetryUntil.operator;
let retryWhile = CompletableRetryWhile.operator;

let subscribe = CompletableSubscribe.operator;
let subscribeOn = CompletableSubscribeOn.operator;

let takeUntil = CompletableTakeUntil.operator;
let timeout = CompletableTimeout.operator;
let timer = CompletableTimer.operator;
let toMaybe = MaybeFromCompletable.operator;
let toObservable = ObservableFromCompletable.operator;
let toSingle = SingleFromCompletable.operator;
let toSingleDefault = SingleFromCompletableDefault.operator;
let toSingleSupplier = SingleFromCompletableSupplier.operator;

let unsubscribeOn = CompletableUnsubscribeOn.operator;