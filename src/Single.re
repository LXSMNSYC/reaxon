let ambArray: Utils.func(array(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleAmbArray.operator;
let ambList: Utils.func(list(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleAmbList.operator;
let ambWith: Utils.bifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleAmbWith.operator;

let cache: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleCache.operator;
let contains: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleContains.operator;

let error: Utils.func(exn, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleError.operator;

let defer: Utils.func(Utils.supplier(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDefer.operator;
let delay: Utils.trifunc(int, Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDelay.operator;
let delaySubscription: Utils.trifunc(int, Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDelaySubscription.operator;
let delayUntil: Utils.bifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDelayUntil.operator;
let dematerialize: Utils.func(SingleTypes.t({..}, Notification.Single.t('a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDematerialize.operator;
let doAfterSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoAfterSuccess.operator;
let doAfterTerminate: Utils.bifunc(Utils.action, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoAfterTerminate.operator;
let doFinally: Utils.bifunc(Utils.action, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoFinally.operator;
let doOnCancel: Utils.bifunc(Utils.action, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnCancel.operator;
let doOnError: Utils.bifunc(Utils.consumer(exn), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnError.operator;
let doOnEvent: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnEvent.operator;
let doOnSubscribe: Utils.bifunc(Utils.consumer(SingleTypes.subscription), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnSubscribe.operator;
let doOnSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnSuccess.operator;
let doOnTerminate: Utils.bifunc(Utils.action, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleDoOnTerminate.operator;

let equals: Utils.bifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, bool)) = SingleEquals.operator;

let flatMap: Utils.bifunc(Utils.func('a, SingleTypes.t({..}, 'b)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, 'b)) = SingleFlatMap.operator;
let flatMapCompletable: Utils.bifunc(Utils.func('a, CompletableTypes.t({..})), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), CompletableTypes.t({..})) = SingleFlatMapCompletable.operator;
let flatMapMaybe: Utils.bifunc(Utils.func('a, MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = SingleFlatMapMaybe.operator;
let flatMapObservable: Utils.bifunc(Utils.func('a, ObservableTypes.t({..}, 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), ObservableTypes.t({..}, 'a)) = SingleFlatMapObservable.operator;
let flattenToObservable: Utils.bifunc(Utils.func('a, list('a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), ObservableTypes.t({..}, 'a)) = SingleFlattenToObservable.operator;
let filter: Utils.bifunc(Utils.predicate('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), MaybeTypes.t(MaybeTypes.observer({..}, 'a), 'a)) = SingleFilter.operator;
let fromObservable: Utils.func(ObservableTypes.t({..}, 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleFromObservable.operator;
let fromSingle: Utils.bifunc(Utils.supplier('a), CompletableTypes.t({..}), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleFromCompletableSupplier.operator;
let fromSingleDefault: Utils.bifunc('a, CompletableTypes.t({..}), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleFromCompletableDefault.operator;
let fromSupplier: Utils.func(Utils.supplier('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleFromSupplier.operator;

let hide: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleHide.operator;

let ignoreElement: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let just: Utils.func('a, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleJust.operator;

let lift: Utils.bifunc(Utils.func(SingleTypes.observer({..}, 'a), SingleTypes.observer({..}, 'b)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, 'b)) = SingleLift.operator;

let make: Utils.func(Utils.consumer(SingleTypes.emitter({..}, 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleMake.operator;
let map: Utils.bifunc(Utils.func('a, 'b), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, 'b)) = SingleMap.operator;
let materialize: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, Notification.Single.t('a))) = SingleMaterialize.operator;
let merge: Utils.func(SingleTypes.t({..}, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleMerge.operator;

let never: Utils.supplier(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleNever.operator;

let observeOn: Utils.bifunc(Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleObserveOn.operator;
let onErrorResume: Utils.bifunc(Utils.func(exn, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleOnErrorResume.operator;
let onErrorResumeNext: Utils.bifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleOnErrorResumeNext.operator;
let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleOnErrorReturn.operator;

let onErrorReturnItem: Utils.bifunc('a, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleOnErrorReturnItem.operator;

let retry: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleRetry.operator;
let retryCount: Utils.bifunc(int, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleRetryWhile.operator;

let subscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleSubscribeOn.operator;

let takeUntil: Utils.bifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, SingleTypes.t({..}, int)) = SingleTimer.operator;
let toCompletable: Utils.func(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = SingleUnsubscribeOn.operator;

let zipArray: Utils.bifunc(array(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), Utils.func(array('a), 'b), SingleTypes.t({..}, 'b)) = SingleZipArray.operator;
let zipList: Utils.bifunc(list(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)), Utils.func(array('a), 'b), SingleTypes.t({..}, 'b)) = SingleZipList.operator;
let zipWith: Utils.trifunc(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), Utils.bifunc('a, 'a, 'b), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.t({..}, 'b)) = SingleZipWith.operator;

let subscribe: Utils.bifunc(SingleTypes.recordObserver('a), SingleTypes.t(SingleTypes.observer({..}, 'a), 'a), SingleTypes.subscription) = SingleSubscribe.operator;