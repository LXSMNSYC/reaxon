
let ambList: Utils.func(list(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableAmbList.operator;
let ambArray : Utils.func(array(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableAmbArray.operator;
let ambWith: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableAmbWith.operator;
let andThen: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableConcatWith.operator;

let cache: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableCache.operator;
let complete: Utils.supplier(CompletableTypes.t({..})) = CompletableComplete.operator;
let concatList: Utils.func(list(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableConcatList.operator;
let concatArray: Utils.func(array(CompletableTypes.t({..})), CompletableTypes.t({..})) = CompletableConcatArray.operator;
let concatWith: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableConcatWith.operator;


let defer: Utils.func(Utils.supplier(CompletableTypes.t({..})), CompletableTypes.t({..})) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => obs#onError(e);  
  };
};

let delayUntil: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();

        source#subscribeWith({
          pub onSubscribe = state#link;

          pub onComplete = obs#onComplete;

          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    })
  }
};

let doAfterTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        obs#onComplete();
        onTerminate();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};

let doFinally: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onFinally, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            sub#cancel();
            onFinally();
          }
        });
      };
  
      pub onComplete = () => {
        obs#onComplete();
        onFinally();
      };
  
      pub onError = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
  };
};

let doOnCancel: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onCancel, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            onCancel();
            sub#cancel();
          }
        });
      };
  
      pub onComplete = obs#onComplete;
  
      pub onError = obs#onError;
    });
  };
};

let doOnError: Utils.bifunc(Utils.consumer(exn), CompletableTypes.t({..}), CompletableTypes.t({..})) = (onError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = obs#onComplete;
  
      pub onError = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};

let doOnEvent: Utils.bifunc(Utils.consumer(Utils.option(exn)), CompletableTypes.t({..}), CompletableTypes.t({..})) = (onEvent, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        onEvent(None);
        obs#onComplete();
      };
  
      pub onError = (x) => {
        onEvent(Some(x));
        obs#onError(x);
      };
    });
  };
};

let doOnSubscribe: Utils.bifunc(Utils.consumer(CompletableTypes.subscription), CompletableTypes.t({..}), CompletableTypes.t({..})) = (onSubscribe, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onComplete = obs#onComplete;

      pub onError = obs#onError;
    });
  };
};

let doOnComplete: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onComplete, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        onComplete();
        obs#onComplete();
      };

      pub onError = obs#onError;
    });
  };
};

let doOnTerminate: Utils.bifunc(Utils.action, CompletableTypes.t({..}), CompletableTypes.t({..})) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onComplete = () => {
        onTerminate();
        obs#onComplete();
      };
  
      pub onError  = (x) => {
        onTerminate();
        obs#onError(x);
      };
    });
  };
};

let error: Utils.func(exn, CompletableTypes.t({..})) = CompletableError.operator;

let fromAction: Utils.func(Utils.action, CompletableTypes.t({..})) = CompletableFromAction.operator;
let fromSupplier: Utils.func(Utils.supplier('a), CompletableTypes.t({..})) = CompletableFromSupplier.operator;
let fromSingle: Utils.func(SingleTypes.t({..}, 'a), CompletableTypes.t({..})) = CompletableFromSingle.operator;

let make: Utils.func(Utils.consumer(CompletableTypes.emitter({..})), CompletableTypes.t({..})) = CompletableMake.operator;

let retry: Utils.func(CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetry.operator;
let retryCount: Utils.bifunc(int, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetryCount.operator;
let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableRetryCount.operator;

let subscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableSubscribeOn.operator;

let takeUntil: Utils.bifunc(CompletableTypes.t({..}), CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableTakeUntil.operator;
let timeout: Utils.trifunc(int, Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableTimeout.operator;
let timer: Utils.bifunc(int, Scheduler.t, CompletableTypes.t({..})) = CompletableTimer.operator;

let unsubscribeOn: Utils.bifunc(Scheduler.t, CompletableTypes.t({..}), CompletableTypes.t({..})) = CompletableUnsubscribeOn.operator;

let subscribe: Utils.bifunc(CompletableTypes.recordObserver, CompletableTypes.t({..}), CompletableTypes.subscription) = CompletableSubscribe.operator;