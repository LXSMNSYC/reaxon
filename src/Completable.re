
let ambList: Utils.func(list(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableAmbList.operator;
let ambArray : Utils.func(array(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableAmbArray.operator;
let ambWith: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableAmbWith.operator;
let andThen: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableConcatWith.operator;
let andThenMaybe: Utils.bifunc(MaybeTypes.t({..}, 'a), CompletableTypes.t({..}), MaybeTypes.t({..}, 'a)) = CompletableAndThenMaybe.operator;
let andThenObservable: Utils.bifunc(ObservableTypes.t({..}, 'a), CompletableTypes.t({..}), ObservableTypes.t({..}, 'a)) = CompletableAndThenObservable.operator;
let andThenSingle: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), CompletableTypes.t({..}), SingleTypes.operator({..}, 'a)) = CompletableAndThenSingle.operator;

let cache: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableCache.operator;
let complete: Utils.supplier(CompletableTypes.t({..})) = CompletableComplete.operator;
let concatList: Utils.func(list(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableConcatList.operator;
let concatArray: Utils.func(array(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableConcatArray.operator;
let concatWith: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableConcatWith.operator;

let defer: Utils.func(Utils.supplier(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableDefer.operator;
let delay: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDelay.operator;
let delaySubscription: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDelaySubscription.operator;
let delayUntil: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDelayUntil.operator;
let dematerialize: Utils.func(SingleTypes.t({..}, {..}, Notification.Completable.t), CompletableTypes.t({..})) = CompletableDematerialize.operator;
let doAfterTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoAfterTerminate.operator;
let doFinally: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoFinally.operator;
let doOnCancel: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnCancel.operator;
let doOnError: Utils.bifunc(Utils.consumer(exn), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnError.operator;
let doOnEvent: Utils.bifunc(Utils.consumer(Utils.option(exn)), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnEvent.operator;
let doOnSubscribe: Utils.bifunc(Utils.consumer(CompletableTypes.subscription), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnSubscribe.operator;
let doOnComplete: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnComplete.operator;
let doOnTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableDoOnTerminate.operator;

let error: Utils.func(exn, CompletableTypes.t({..})) = CompletableError.operator;

let fromAction: Utils.func(Utils.action, CompletableTypes.t({..})) = CompletableFromAction.operator;
let fromSupplier: Utils.func(Utils.supplier('a), CompletableTypes.t({..})) = CompletableFromSupplier.operator;
let fromSingle: Utils.func(SingleTypes.t({..}, {..}, 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let hide: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableHide.operator;

let make: Utils.func(Utils.consumer(CompletableTypes.emitter({..})), CompletableTypes.t({..})) = CompletableMake.operator;
let materialize: Utils.func(CompletableTypes.t({..}), SingleTypes.operator({..}, Notification.Completable.t)) = CompletableMaterialize.operator;

let observeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableObserveOn.operator;
let onErrorComplete: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableOnErrorComplete.operator;
let onErrorCompleteWhen: Utils.bifunc(Utils.func(exn, bool), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableOnErrorCompleteWhen.operator;
let onErrorResume: Utils.bifunc(Utils.func(exn, CompletableTypes.t({..})), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableOnErrorResume.operator;
let onErrorResumeNext: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableOnErrorResumeNext.operator;

let retry: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetry.operator;
let retryCount: Utils.bifunc(int, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetryWhile.operator;


let subscribe: Utils.bifunc(CompletableTypes.recordObserver, CompletableTypes.t({..}), CompletableTypes.subscription) = CompletableSubscribe.operator;
let subscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableSubscribeOn.operator;

let takeUntil: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, CompletableTypes.t({..})) = CompletableTimer.operator;
let toMaybe: Utils.func(CompletableTypes.t({..}), MaybeTypes.t({..}, 'a)) = MaybeFromCompletable.operator;
let toSingle: Utils.bifunc(Utils.supplier('a), CompletableTypes.t({..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableSupplier.operator;
let toSingleDefault: Utils.bifunc('a, CompletableTypes.t({..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableDefault.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableUnsubscribeOn.operator;