
exception CancellationException;


type subscription = Cancellable.Boolean.i;


type observer('observer, 'a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'observer;


type t('observer,'a) = {
  .
  subscribeWith: Utils.consumer(observer('observer, 'a)),
};


type emitter('emitter, 'a) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.supplier(bool),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'emitter;


let ambList: Utils.func(list(t({..}, 'a)), t({..}, 'a)) = (singleList) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    singleList |> List.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};



let ambArray: Utils.func(array(t({..}, 'a)), t({..}, 'a)) = (singleArray) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    singleArray |> Array.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        obs#onSuccess(x);
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};


let ambWith: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a)) = (a, b) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    a#subscribeWith({
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

    b#subscribeWith({
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


let cache: Utils.func(t({..}, 'a), t({..}, 'a)) = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(observer({..}, 'a))) = ref([]);
  val success = ref(None);
  val error = ref(None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        switch (success^) {
          | Some(x) => obs#onSuccess(x)
          | None => switch(error^) {
            | Some(e) => obs#onError(e)
            | None => () 
          }
        };
  
        state#cancel();
      }
    } else {
      let state = Cancellable.Boolean.make();

      observers := [obs] @ observers^;

      let subscription = {
        pub isCancelled = state#isCancelled;
        pub cancel = () => {
          observers := observers^ |> List.filter(x => x != obs);
          state#cancel();
        };
      };

      obs#onSubscribe(subscription);

      if (!subscribed^) {
        subscribed := true;
        source#subscribeWith({
          pub onSubscribe = (sub) => ();
  
          pub onSuccess = (x) => {
            cached := true;
            success := Some(x);

            observers^ |> List.iter(o => o#onSuccess(x));
            subscription#cancel();
          };

          pub onError = (e) => {
            cached := true;
            error := Some(e);

            observers^ |> List.iter(o => o#onError(e));
            subscription#cancel();
          };
        });
      }
    }
  };
};


let contains: Utils.trifunc('a, Utils.option(Utils.bipredicate('a, 'a)), t({..}, 'a), t({..}, 'a)) = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        switch(comparer) {
          | Some(cmp) => {
            switch (cmp(x, item)) {
              | result => obs#onSuccess(result)
              | exception e => obs#onError(e);
            };
          }
          | None => obs#onSuccess(x == item)
        };
        state#cancel();
      };

      pub onError = obs#onError;
    })
  };
};

let error: Utils.func(exn, t({..}, 'a)) = (err) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onError(err);
      state#cancel();
    }
  };
};



let defer: Utils.func(Utils.supplier(t({..}, 'a)), t({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => error(e)#subscribeWith(obs);
  };
};

let delay: Utils.trifunc(int, Scheduler.t, t({..}, 'a), t({..}, 'a)) = (time, scheduler, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onSuccess(x);
        }, time));
      };

      pub onError = (x) => {
        state#link(scheduler#timeout(() => {
          obs#onError(x);
        }, time));
      };
    });
  };
};


let delayUntil: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#unlink();

        source#subscribeWith({
          pub onSubscribe = state#link;

          pub onSuccess = obs#onSuccess;

          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    })
  }
};


let doAfterSuccess: Utils.bifunc(Utils.consumer('a), t({..}, 'a), t({..}, 'a)) = (onSuccess, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
  
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onSuccess(x);
      };
  
      pub onError = obs#onError;
    });
  };
};

let doAfterTerminate: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };
  
      pub onError  = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};

let doFinally: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onFinally, source) => {
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
  
      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onFinally();
      };
  
      pub onError  = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
  };
};

let doOnCancel: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onCancel, source) => {
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
  
      pub onSuccess = obs#onSuccess;
  
      pub onError = obs#onError;
    });
  };
};

let doOnError: Utils.bifunc(Utils.consumer(exn), t({..}, 'a), t({..}, 'a)) = (onError, source) => {
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
        onError(x);
        obs#onError(x);
      };
    });
  };
};

let doOnEvent: Utils.bifunc(Utils.biconsumer(Utils.option('a), Utils.option(exn)), t({..}, 'a), t({..}, 'a)) = (onEvent, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        onEvent(Some(x), None);
        obs#onSuccess(x);
      };
  
      pub onError = (x) => {
        onEvent(None, Some(x));
        obs#onError(x);
      };
    });
  };
};

let doOnSubscribe: Utils.bifunc(Utils.consumer(subscription), t({..}, 'a), t({..}, 'a)) = (onSubscribe, source) => {
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

      pub onSuccess = obs#onSuccess;

      pub onError = obs#onError;
    });
  };
};

let doOnSuccess: Utils.bifunc(Utils.consumer('a), t({..}, 'a), t({..}, 'a)) = (onSuccess, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        onSuccess(x);
        obs#onSuccess(x);
      };

      pub onError = obs#onError;
    });
  };
};

let doOnTerminate: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onTerminate, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;
  
      pub onSuccess = (x) => {
        onTerminate();
        obs#onSuccess(x);
      };
  
      pub onError  = (x) => {
        onTerminate();
        obs#onError(x);
      };
    });
  };
};

let equals: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, bool)) = (a, b) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let aValue = ref(None);
    let bValue = ref(None);

    a#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch(bValue^) {
          | Some(bval) => {
            obs#onSuccess(bval == x);
            state#cancel();
          }
          | None => {
            aValue := Some(x);
          }
        };
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    b#subscribeWith({
      pub onSubscribe = state#add;

      pub onSuccess = (x) => {
        switch(aValue^) {
          | Some(aval) => {
            obs#onSuccess(aval == x);
            state#cancel();
          }
          | None => {
            bValue := Some(x);
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

let flatMap: Utils.bifunc(Utils.func('a, t({..}, 'b)), t({..}, 'a), t({..}, 'b)) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        switch(mapper(x)) {
          | item => {
            state#unlink();
            item#subscribeWith({
              pub onSubscribe = state#link;

              pub onSuccess = obs#onSuccess;

              pub onError = obs#onError;
            });
          }
          | exception e => obs#onError(e)
        }
      };

      pub onError = obs#onError;
    });
    
  };
};

let flatMap: Utils.bifunc(Utils.func('a, Completable.t({..})), t({..}, 'a), Completable.t({..})) = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        switch(mapper(x)) {
          | item => {
            state#unlink();
            item#subscribeWith({
              pub onSubscribe = state#link;

              pub onComplete = obs#onComplete;

              pub onError = obs#onError;
            });
          }
          | exception e => obs#onError(e)
        }
      };

      pub onError = obs#onError;
    });
    
  };
};

let fromsupplier: Utils.func(Utils.supplier('a), t({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (supplier()) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e)
      };
      state#cancel();
    }
  };
};

let hide: Utils.func(t({..}, 'a), t({..}, 'a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = obs#onSuccess;
      
      pub onError = obs#onError;
    });
  };
};

let ignoreElement: Utils.func(t({..}, 'a), Completable.t({..})) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => obs#onComplete();
      
      pub onError = obs#onError;
    });
  };
};

let just: Utils.func('a, t({..}, 'a)) = (value) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onSuccess(value);
      state#cancel();
    }
  };
};

let lift: Utils.bifunc(Utils.func(observer({..}, 'a), observer({..}, 'b)), t({..}, 'a), t({..}, 'b)) = (operator, source) => {
  pub subscribeWith = (obs) => switch(operator(obs)) {
    | newObserver => source#subscribeWith(newObserver)
    | exception e => error(e)#subscribeWith(obs)
  };
}

let make: Utils.func(Utils.consumer(emitter({..}, 'a)), t({..}, 'a)) = (onSubscribe) => {
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

let map: Utils.bifunc(Utils.func('a, 'b), t({..}, 'a), t({..}, 'b)) = (mapper, source) => {
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

let never: Utils.supplier(t({..}, 'a)) = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};

let observeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a)) = (scheduler, source) => {
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

let onErrorResume: Utils.bifunc(Utils.func(exn, t({..}, 'a)), t({..}, 'a), t({..}, 'a)) = (resumeIfError, source) => {
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

let onErrorResumeNext: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a)) = (resumeIfError, source) => {
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

let onErrorReturn: Utils.bifunc(Utils.func(exn, 'a), t({..}, 'a), t({..}, 'a)) = (resumeFunction, source) => {
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

let onErrorReturnItem: Utils.bifunc('a, t({..}, 'a), t({..}, 'a)) = (item, source) => {
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

let retry: Utils.func(t({..}, 'a), t({..}, 'a)) = (source) => {
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

let retryCount: Utils.bifunc(int, t({..}, 'a), t({..}, 'a)) = (count, source) => {
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

let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), t({..}, 'a), t({..}, 'a)) = (checker, source) => {
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

let subscribeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a)) = (scheduler, source) => {
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

let takeUntil: Utils.bifunc(t({..}, 'a), t({..}, 'a), t({..}, 'a)) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

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

let unsubscribeOn: Utils.bifunc(Scheduler.t, t({..}, 'a), t({..}, 'a)) = (scheduler, source) => {
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

let zipArray: Utils.bifunc(array(t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b)) = (singleArray, combiner) => {
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

let zipList: Utils.bifunc(list(t({..}, 'a)), Utils.func(array('a), 'b), t({..}, 'b)) = (singleList, combiner) => {
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

let zipWith: Utils.trifunc(t({..}, 'a), Utils.bifunc('a, 'a, 'b), t({..}, 'a), t({..}, 'b)) = (other, combiner, source) => {
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

let subscribe: Utils.bifunc(basicObserver('a), t({..}, 'a), subscription) = (obs, source) => {
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