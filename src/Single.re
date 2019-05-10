let ambArray: Utils.func(array(SingleTypes.t({..}, {..}, 'a)), SingleTypes.operator({..}, 'a)) = SingleAmbArray.operator;
let ambList: Utils.func(list(SingleTypes.t({..}, {..}, 'a)), SingleTypes.operator({..}, 'a)) = SingleAmbList.operator;
let ambWith: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a), SingleTypes.operator({..}, 'a)) = SingleAmbWith.operator;

let cache: Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleCache.operator;
let contains: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleContains.operator;

let error: Utils.func(exn, SingleTypes.operator({..}, 'a)) = SingleError.operator;

let defer: Utils.func(Utils.supplier(SingleTypes.t({..}, {..}, 'a)), SingleTypes.operator({..}, 'a)) = SingleDefer.operator;
let delay: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDelay.operator;
let delaySubscription: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDelaySubscription.operator;
let delayUntil: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDelayUntil.operator;
let dematerialize: Utils.func(SingleTypes.t({..}, {..}, Notification.Single.t('a)), SingleTypes.operator({..}, 'a)) = SingleDematerialize.operator;
let doAfterSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoAfterSuccess.operator;
let doAfterTerminate: Utils.bifunc(Utils.action, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoAfterTerminate.operator;
let doFinally: Utils.bifunc(Utils.action, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoFinally.operator;
let doOnCancel: Utils.bifunc(Utils.action, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnCancel.operator;
let doOnError: Utils.bifunc(Utils.consumer(exn), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnError.operator;
let doOnEvent: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnEvent.operator;
let doOnSubscribe: Utils.bifunc(Utils.consumer(SingleTypes.subscription), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnSubscribe.operator;
let doOnSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnSuccess.operator;
let doOnTerminate: Utils.bifunc(Utils.action, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleDoOnTerminate.operator;

let equals: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, bool)) = SingleEquals.operator;

let flatMap: Utils.bifunc(Utils.func('a, SingleTypes.t({..}, {..}, 'b)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = SingleFlatMap.operator;
let flatMapCompletable: Utils.bifunc(Utils.func('a, CompletableTypes.t({..}, {..})), SingleTypes.t({..}, {..}, 'a), CompletableTypes.operator({..})) = SingleFlatMapCompletable.operator;
let flatMapMaybe: Utils.bifunc(Utils.func('a, MaybeTypes.t({..}, {..}, 'a)), SingleTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = SingleFlatMapMaybe.operator;
let flatMapObservable: Utils.bifunc(Utils.func('a, ObservableTypes.t({..}, 'a)), SingleTypes.t({..}, {..}, 'a), ObservableTypes.t({..}, 'a)) = SingleFlatMapObservable.operator;
let flattenToObservable: Utils.bifunc(Utils.func('a, list('a)), SingleTypes.t({..}, {..}, 'a), ObservableTypes.t({..}, 'a)) = SingleFlattenToObservable.operator;
let filter: Utils.bifunc(Utils.predicate('a), SingleTypes.t({..}, {..}, 'a), MaybeTypes.operator({..}, 'a)) = SingleFilter.operator;
let fromObservable: Utils.func(ObservableTypes.t({..}, 'a), SingleTypes.operator({..}, 'a)) = SingleFromObservable.operator;
let fromSingle: Utils.bifunc(Utils.supplier('a), CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableSupplier.operator;
let fromSingleDefault: Utils.bifunc('a, CompletableTypes.t({..}, {..}), SingleTypes.operator({..}, 'a)) = SingleFromCompletableDefault.operator;
let fromSupplier: Utils.func(Utils.supplier('a), SingleTypes.operator({..}, 'a)) = SingleFromSupplier.operator;

let hide: Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleHide.operator;

let ignoreElement: Utils.func(SingleTypes.t({..}, {..}, 'a), CompletableTypes.operator({..})) = CompletableFromSingle.operator;

let just: Utils.func('a, SingleTypes.operator({..}, 'a)) = SingleJust.operator;

let lift: Utils.bifunc(Utils.func(SingleTypes.observer({..}, 'a), SingleTypes.observer({..}, 'b)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = SingleLift.operator;

let make: Utils.func(Utils.consumer(SingleTypes.emitter({..}, 'a)), SingleTypes.operator({..}, 'a)) = SingleMake.operator;
let map: Utils.bifunc(Utils.func('a, 'b), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = SingleMap.operator;
let materialize: Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, Notification.Single.t('a))) = SingleMaterialize.operator;
let merge: Utils.func(SingleTypes.t({..}, {..}, SingleTypes.t({..}, {..}, 'a)), SingleTypes.operator({..}, 'a)) = SingleMerge.operator;

let never: Utils.supplier(SingleTypes.operator({..}, 'a)) = SingleNever.operator;

let observeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleObserveOn.operator;
let onErrorResume: Utils.bifunc(Utils.func(exn, SingleTypes.t({..}, {..}, 'a)), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleOnErrorResume.operator;
let onErrorResumeNext: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleOnErrorResumeNext.operator;
let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleOnErrorReturn.operator;

let onErrorReturnItem: Utils.bifunc('a, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleOnErrorReturnItem.operator;

let retry: Utils.func(SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleRetry.operator;
let retryCount: Utils.bifunc(int, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleRetryWhile.operator;

let subscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleSubscribeOn.operator;

let takeUntil: Utils.bifunc(SingleTypes.t({..}, {..}, 'a), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, SingleTypes.operator({..}, int)) = SingleTimer.operator;
let toCompletable: Utils.func(SingleTypes.t({..}, {..}, 'a), CompletableTypes.operator({..})) = CompletableFromSingle.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'a)) = SingleUnsubscribeOn.operator;

let zipArray: Utils.bifunc(array(SingleTypes.t({..}, {..}, 'a)), Utils.func(array('a), 'b), SingleTypes.operator({..}, 'b)) = SingleZipArray.operator;
let zipList: Utils.bifunc(list(SingleTypes.t({..}, {..}, 'a)), Utils.func(array('a), 'b), SingleTypes.operator({..}, 'b)) = SingleZipList.operator;
let zipWith: Utils.trifunc(SingleTypes.t({..}, {..}, 'a), Utils.bifunc('a, 'a, 'b), SingleTypes.t({..}, {..}, 'a), SingleTypes.operator({..}, 'b)) = SingleZipWith.operator;

let subscribe: Utils.bifunc(SingleTypes.recordObserver('a), SingleTypes.t({..}, {..}, 'a), SingleTypes.subscription) = SingleSubscribe.operator;