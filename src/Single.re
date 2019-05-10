let ambArray: Utils.func(array(SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a)) = SingleAmbArray.operator;
let ambList: Utils.func(list(SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a)) = SingleAmbList.operator;
let ambWith: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleAmbWith.operator;

let cache: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleCache.operator;
let contains: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleContains.operator;

let error: Utils.func(exn, SingleTypes.t({..}, 'a)) = SingleError.operator;

let defer: Utils.func(Utils.supplier(SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a)) = SingleDefer.operator;
let delay: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDelay.operator;
let delaySubscription: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDelaySubscription.operator;
let delayUntil: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDelayUntil.operator;
let dematerialize: Utils.func(SingleTypes.t({..}, Notification.Single.t('a)), SingleTypes.t({..}, 'a)) = SingleDematerialize.operator;
let doAfterSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoAfterSuccess.operator;
let doAfterTerminate: Utils.bifunc(Utils.action, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoAfterTerminate.operator;
let doFinally: Utils.bifunc(Utils.action, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoFinally.operator;
let doOnCancel: Utils.bifunc(Utils.action, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnCancel.operator;
let doOnError: Utils.bifunc(Utils.consumer(exn), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnError.operator;
let doOnEvent: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnEvent.operator;
let doOnSubscribe: Utils.bifunc(Utils.consumer(SingleTypes.subscription), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnSubscribe.operator;
let doOnSuccess: Utils.bifunc(Utils.consumer('a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnSuccess.operator;
let doOnTerminate: Utils.bifunc(Utils.action, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleDoOnTerminate.operator;

let equals: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, bool)) = SingleEquals.operator;

let flatMap: Utils.bifunc(Utils.func('a, SingleTypes.t({..}, 'b)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'b)) = SingleFlatMap.operator;
let flatMapCompletable: Utils.bifunc(Utils.func('a, CompletableTypes.t({..})), SingleTypes.t({..}, 'a), CompletableTypes.t({..})) = SingleFlatMapCompletable.operator;
let flatMapMaybe: Utils.bifunc(Utils.func('a, MaybeTypes.t({..}, 'a)), SingleTypes.t({..}, 'a), MaybeTypes.t({..}, 'a));
let flatMapObservable: Utils.bifunc(Utils.func('a, ObservableTypes.t({..}, 'a)), SingleTypes.t({..}, 'a), ObservableTypes.t({..}, 'a)) = SingleFlatMapObservable.operator;
let filter: Utils.bifunc(Utils.predicate('a), SingleTypes.t({..}, 'a), MaybeTypes.t({..}, 'a)) = SingleFilter.operator;
let fromObservable: Utils.func(ObservableTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleFromObservable.operator;
let fromPublisher: Utils.func(ReactiveStreams.publisher({..}, {..}, {..}, 'a), SingleTypes.t({..}, 'a)) = SingleFromPublisher.operator;
let fromSupplier: Utils.func(Utils.supplier('a), SingleTypes.t({..}, 'a)) = SingleFromSupplier.operator;

let hide: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleHide.operator;

let ignoreElement: Utils.func(SingleTypes.t({..}, 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let just: Utils.func('a, SingleTypes.t({..}, 'a)) = SingleJust.operator;

let lift: Utils.bifunc(Utils.func(SingleTypes.observer({..}, 'a), SingleTypes.observer({..}, 'b)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'b)) = SingleLift.operator;

let make: Utils.func(Utils.consumer(SingleTypes.emitter({..}, 'a)), SingleTypes.t({..}, 'a)) = SingleMake.operator;
let map: Utils.bifunc(Utils.func('a, 'b), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'b)) = SingleMap.operator;
let materialize: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, Notification.Single.t('a))) = SingleMaterialize.operator;
let never: Utils.supplier(SingleTypes.t({..}, 'a)) = SingleNever.operator;

let observeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleObserveOn.operator;
let onErrorResume: Utils.bifunc(Utils.func(exn, SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleOnErrorResume.operator;
let onErrorResumeNext: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleOnErrorResumeNext.operator;
let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleOnErrorReturn.operator;

let onErrorReturnItem: Utils.bifunc('a, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleOnErrorReturnItem.operator;

let retry: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleRetry.operator;
let retryCount: Utils.bifunc(int, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleRetryWhile.operator;

let subscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleSubscribeOn.operator;

let takeUntil: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, SingleTypes.t({..}, 'a)) = SingleTimer.operator;
let toCompletable: Utils.func(SingleTypes.t({..}, 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleUnsubscribeOn.operator;

let zipArray: Utils.bifunc(array(SingleTypes.t({..}, 'a)), Utils.func(array('a), 'b), SingleTypes.t({..}, 'b)) = SingleZipArray.operator;
let zipList: Utils.bifunc(list(SingleTypes.t({..}, 'a)), Utils.func(array('a), 'b), SingleTypes.t({..}, 'b)) = SingleZipList.operator;
let zipWith: Utils.trifunc(SingleTypes.t({..}, 'a), Utils.bifunc('a, 'a, 'b), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'b)) = SingleZipWith.operator;

let subscribe: Utils.bifunc(SingleTypes.recordObserver('a), SingleTypes.t({..}, 'a), SingleTypes.subscription) = SingleSubscribe.operator;