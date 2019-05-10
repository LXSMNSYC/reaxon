
exception CancellationException;
exception TimeoutException;
exception IndexOutOfBoundsException;
exception NoSuchElementException;


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

let fromObservable: Utils.func(ObservableTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleFromObservable.operator;
let fromPublisher: Utils.func(ReactiveStreams.publisher({..}, {..}, {..}, 'a), SingleTypes.t({..}, 'a)) = SingleFromPublisher.operator;
let fromSupplier: Utils.func(Utils.supplier('a), SingleTypes.t({..}, 'a)) = SingleFromSupplier.operator;

let hide: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = SingleHide.operator;

let just: Utils.func('a, SingleTypes.t({..}, 'a)) = (value) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onSuccess(value);
      state#cancel();
    }
  };
};

let lift: Utils.bifunc(Utils.func(observer({..}, 'a), observer({..}, 'b)), SingleTypes.t({..}, 'a), t({..}, 'b)) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => error(e)#subscribeWith(obs)
  };
}

let make: Utils.func(Utils.consumer(emitter({..}, 'a)), SingleTypes.t({..}, 'a)) = (onSubscribe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let e = {
      pub setCancellable = state#link;
  
      pub isCancelled = () => state#isCancelled();
    
      pub onSuccess = (x: 'a) => {
        if (!state#isCancelled()) {
          obs#onSuccess(x);
          state#cancel();
        }
      };
  
      pub onError = (x: exn) => {
        if (!state#isCancelled()) {
          obs#onError(x);
          state#cancel();
        }
      };
    };

    try(onSubscribe(e)) {
      | err => e#onError(err)
    };
  };
};

let map: Utils.bifunc(Utils.func('a, 'b), SingleTypes.t({..}, 'a), t({..}, 'b)) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => switch(mapper(x)) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e) 
      };

      pub onError = obs#onError;
    })
  };
};

let never: Utils.supplier(SingleTypes.t({..}, 'a)) = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};

let observeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => state#link(scheduler#run(() => {
        obs#onSuccess(x);
      }));

      pub onError = (x) => state#link(scheduler#run(() => {
        obs#onError(x);
      }));
    })
  };
}

let onErrorResume: Utils.bifunc(Utils.func(exn, SingleTypes.t({..}, 'a)), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (resumeIfError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = (x) => {
        switch (resumeIfError(x)) {
          | newSource => {
            state#unlink();
            newSource#subscribeWith({
              pub onSubscribe = state#link;
        
              pub onSuccess = obs#onSuccess;

              pub onError = obs#onError;
            });
          }
          | exception e => obs#onError(e) 
        }
      };
    });
  };
};

let onErrorResumeNext: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (resumeIfError, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = (x) => {
        state#unlink();
        resumeIfError#subscribeWith({
          pub onSubscribe = state#link;
    
          pub onSuccess = obs#onSuccess;

          pub onError = obs#onError;
        });
      };
    });
  };
};

let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (resumeFunction, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = (x) => {
        switch (resumeFunction(x)) {
          | item => obs#onSuccess(item)
          | exception e => obs#onError(e)
        };
      };
    });
  };
};

let onErrorReturnItem: Utils.bifunc('a, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (item, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = (x) => obs#onSuccess(item);
    });
  };
};

let retry: Utils.func(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let rec sub = () => {
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onSuccess = obs#onSuccess;

        pub onError = (x) => {
          sub();
        };
      });
    };

    sub();
  };
};

let retryCount: Utils.bifunc(int, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (count, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onSuccess = obs#onSuccess;

        pub onError = (x) => {
          if (retries^ < count) {
            sub();
          } else {
            obs#onError(x);
          }
        };
      });
    };

    sub();
  };
};

let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (checker, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let retries = ref(-1);

    let rec sub = () => {
      retries := retries^ + 1;
      state#unlink();
      source#subscribeWith({
        pub onSubscribe = state#link;

        pub onSuccess = obs#onSuccess;

        pub onError = (x) => {
          if (checker(retries^, x)) {
            sub();
          } else {
            obs#onError(x);
          }
        };
      });
    };

    sub();
  };
};

let subscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    state#link(scheduler#run(() => {
      state#unlink();

      source#subscribeWith({
        pub onSubscribe = state#link;
  
        pub onSuccess = obs#onSuccess;

        pub onError = obs#onError;
      });
    }));
  };
};

let takeUntil: Utils.bifunc(SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onError(CancellationException);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let timer: Utils.bifunc(int, Scheduler.t, SingleTypes.t({..}, 'a)) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onSuccess(0);
    }, time));
  }
};

let timeout: Utils.trifunc(int, Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let clock = state#add(scheduler#timeout(() => {
      obs#onError(TimeoutException);
      state#cancel();
    }, time));

    source#subscribeWith({
      pub onSubscribe = state#add;
      
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };
      
      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let unsubscribeOn: Utils.bifunc(Scheduler.t, SingleTypes.t({..}, 'a), SingleTypes.t({..}, 'a)) = (scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = () => {
        scheduler#run(state#cancel);
        ();
      };
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;

      pub onError = obs#onError;
    });
  };
};

let zipArray: Utils.bifunc(array(SingleTypes.t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b)) = (singleArray, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(singleArray |> Array.length);
    let container = [||];

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    singleArray |> Array.iteri((index, item) => {
      item#subscribeWith({
        pub onSubscribe = state#add;

        pub onSuccess = (x) => {
          Array.set(container, index, x);
          pending := pending^ - 1;

          if (pending^ == 0) {
            switch (combiner(container)) {
              | item => obs#onSuccess(item)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
        };

        pub onError = (x) => {
          obs#onError(x);
          state#cancel();
        }
      })
    });

  };
}

let zipList: Utils.bifunc(list(SingleTypes.t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b)) = (singleList, combiner) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    let pending = ref(singleList |> List.length);
    let container = [||];

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let index = ref(0);

    singleList |> List.iter(item => {
      item#subscribeWith({
        pub onSubscribe = state#add;

        pub onSuccess = (x) => {
          Array.set(container, index^, x);
          pending := pending^ - 1;

          if (pending^ == 0) {
            switch (combiner(container)) {
              | item => obs#onSuccess(item)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
        };

        pub onError = (x) => {
          obs#onError(x);
          state#cancel();
        }
      })
    });
  };
};

let zipWith: Utils.trifunc(SingleTypes.t({..}, 'a), Utils.bifunc('a, 'a, 'b), SingleTypes.t({..}, 'a), t({..}, 'b)) = (other, combiner, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let left = ref(None);
    let right = ref(None);

    source#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch (left^) {
          | Some(value) => {
            switch(combiner(value, x)) {
              | combined => obs#onSuccess(combined)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
          | None => {
            right := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch (right^) {
          | Some(value) => {
            switch(combiner(value, x)) {
              | combined => obs#onSuccess(combined)
              | exception e => obs#onError(e)
            };
            state#cancel();
          }
          | None => {
            left := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

type basicObserver('a) = {
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
};

let subscribe: Utils.bifunc(basicObserver('a), SingleTypes.t({..}, 'a), subscription) = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;

    pub onSuccess = obs.onSuccess;

    pub onError = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};