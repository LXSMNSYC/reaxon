
let ambList: Utils.func(list(CompletableTypes.t({..}, {..})), CompletableTypes.operator({..})) = CompletableAmbList.operator;
let ambArray : Utils.func(array(CompletableTypes.t({..}, {..})), CompletableTypes.operator({..})) = CompletableAmbArray.operator;
let ambWith: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableAmbWith.operator;
let andThen: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableConcatWith.operator;
let andThenMaybe: Utils.bifunc(MaybeTypes.t({..}, {..}, 'a), CompletableTypes.t({..}, {..}), MaybeTypes.operator({..}, 'a)) = CompletableAndThenMaybe.operator;
let andThenObservable: Utils.bifunc(ObservableTypes.t({..}, 'a), CompletableTypes.t({..}, {..}), ObservableTypes.t({..}, 'a)) = CompletableAndThenObservable.operator;
let andThenSingle: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, 'a)) = CompletableAndThenSingle.operator;

let cache: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableCache.operator;
let complete: Utils.supplier(CompletableTypes.operator({..})) = CompletableComplete.operator;
let concatList: Utils.func(list(CompletableTypes.t({..}, {..})), CompletableTypes.operator({..})) = CompletableConcatList.operator;
let concatArray: Utils.func(array(CompletableTypes.t({..}, {..})), CompletableTypes.operator({..})) = CompletableConcatArray.operator;
let concatWith: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableConcatWith.operator;

let defer: Utils.func(Utils.supplier(CompletableTypes.t({..}, {..})), CompletableTypes.operator({..})) = CompletableDefer.operator;
let delay: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDelay.operator;
let delaySubscription: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDelaySubscription.operator;
let delayUntil: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDelayUntil.operator;
let dematerialize: Utils.func(SingleTypes.t({..}, {..}, Notification.Completable.t), CompletableTypes.operator({..})) = CompletableDematerialize.operator;
let doAfterTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoAfterTerminate.operator;
let doFinally: Utils.bifunc(Utils.action, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoFinally.operator;
let doOnCancel: Utils.bifunc(Utils.action, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnCancel.operator;
let doOnError: Utils.bifunc(Utils.consumer(exn), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnError.operator;
let doOnEvent: Utils.bifunc(Utils.consumer(Utils.option(exn)), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnEvent.operator;
let doOnSubscribe: Utils.bifunc(Utils.consumer(CompletableTypes.subscription), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnSubscribe.operator;
let doOnComplete: Utils.bifunc(Utils.action, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnComplete.operator;
let doOnTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableDoOnTerminate.operator;

let error: Utils.func(exn, CompletableTypes.operator({..})) = CompletableError.operator;

let fromAction: Utils.func(Utils.action, CompletableTypes.operator({..})) = CompletableFromAction.operator;
let fromSupplier: Utils.func(Utils.supplier('a), CompletableTypes.operator({..})) = CompletableFromSupplier.operator;
let fromSingle: Utils.func(SingleTypes.t({..}, {..}, 'a), CompletableTypes.operator({..})) = CompletableFromSingle.operator;

let hide: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableHide.operator;

let make: Utils.func(Utils.consumer(CompletableTypes.emitter({..})), CompletableTypes.operator({..})) = CompletableMake.operator;
let materialize: Utils.func(CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, Notification.Completable.t)) = CompletableMaterialize.operator;

let observeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableObserveOn.operator;
let onErrorComplete: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableOnErrorComplete.operator;
let onErrorCompleteWhen: Utils.bifunc(Utils.func(exn, bool), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableOnErrorCompleteWhen.operator;
let onErrorResume: Utils.bifunc(Utils.func(exn, CompletableTypes.t({..}, {..})), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableOnErrorResume.operator;
let onErrorResumeNext: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableOnErrorResumeNext.operator;

let retry: Utils.func(CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableRetry.operator;
let retryCount: Utils.bifunc(int, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableRetryWhile.operator;


let subscribe: Utils.bifunc(CompletableTypes.recordObserver, CompletableTypes.t({..}, {..}), CompletableTypes.subscription) = CompletableSubscribe.operator;
let subscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableSubscribeOn.operator;

let takeUntil: Utils.bifunc(CompletableTypes.t({..}, {..}), CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, CompletableTypes.operator({..})) = CompletableTimer.operator;
let toMaybe: Utils.func(CompletableTypes.t({..}, {..}), MaybeTypes.operator({..}, 'a)) = MaybeFromCompletable.operator;
let toSingle: Utils.bifunc(Utils.supplier('a), CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableSupplier.operator;
let toSingleDefault: Utils.bifunc('a, CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableDefault.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}, {..}), CompletableTypes.operator({..})) = CompletableUnsubscribeOn.operator;