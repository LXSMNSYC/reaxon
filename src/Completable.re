
let ambList = CompletableAmbList.operator;
let ambArray  = CompletableAmbArray.operator;
let ambWith = CompletableAmbWith.operator;
let andThen = CompletableConcatWith.operator;
let andThenMaybe = CompletableAndThenMaybe.operator;
let andThenObservable = CompletableAndThenObservable.operator;
let andThenSingle = CompletableAndThenSingle.operator;

let cache = CompletableCache.operator;
let complete = CompletableComplete.operator;
let concatList = CompletableConcatList.operator;
let concatArray = CompletableConcatArray.operator;
let concatWith = CompletableConcatWith.operator;

let defer = CompletableDefer.operator;
let delay = CompletableDelay.operator;
let delaySubscription = CompletableDelaySubscription.operator;
let delayUntil = CompletableDelayUntil.operator;
let dematerialize = CompletableDematerialize.operator;
let doAfterTerminate = CompletableDoAfterTerminate.operator;
let doFinally = CompletableDoFinally.operator;
let doOnCancel = CompletableDoOnCancel.operator;
let doOnError = CompletableDoOnError.operator;
let doOnEvent = CompletableDoOnEvent.operator;
let doOnSubscribe = CompletableDoOnSubscribe.operator;
let doOnComplete = CompletableDoOnComplete.operator;
let doOnTerminate = CompletableDoOnTerminate.operator;

let error = CompletableError.operator;

let fromAction = CompletableFromAction.operator;
let fromSupplier = CompletableFromSupplier.operator;
let fromSingle = CompletableFromSingle.operator;

let hide = CompletableHide.operator;

let make = CompletableMake.operator;
let materialize = CompletableMaterialize.operator;

let observeOn = CompletableObserveOn.operator;
let onErrorComplete = CompletableOnErrorComplete.operator;
let onErrorCompleteWhen = CompletableOnErrorCompleteWhen.operator;
let onErrorResume = CompletableOnErrorResume.operator;
let onErrorResumeNext = CompletableOnErrorResumeNext.operator;

let retry = CompletableRetry.operator;
let retryCount = CompletableRetryCount.operator;
let retryWhile = CompletableRetryWhile.operator;


let subscribe = CompletableSubscribe.operator;
let subscribeOn = CompletableSubscribeOn.operator;

let takeUntil = CompletableTakeUntil.operator;
let timeout = CompletableTimeout.operator;
let timer = CompletableTimer.operator;
let toMaybe = MaybeFromCompletable.operator;
let toSingle = SingleFromCompletableSupplier.operator;
let toSingleDefault = SingleFromCompletableDefault.operator;

let unsubscribeOn = CompletableUnsubscribeOn.operator;