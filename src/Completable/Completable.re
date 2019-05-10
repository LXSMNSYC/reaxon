exception CancellationException;
exception TimeoutException;


let ambList: Utils.func(list(t({..})), t({..})) = (completableList) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completableList |> List.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};



let ambArray : Utils.func(array(t({..})), t({..})) = (completableArray) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    completableArray |> Array.iter(single => single#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    }));
  };
};


let ambWith: Utils.bifunc(t({..}), t({..}), t({..})) = (a, b) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    a#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });

    b#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let cache: Utils.func(t({..}), t({..})) = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(observer({..}))) = ref([]);
  val complete = ref(false);
  val error = ref(None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe(state);

      if (!state#isCancelled()) {
        if (complete^) {
          obs#onComplete();
        } else {
          switch(error^) {
            | Some(e) => obs#onError(e)
            | None => () 
          };
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
          pub onSubscribe = sub => ();
  
          pub onComplete = () => {
            cached := true;
            complete := true;

            observers^ |> List.iter(o => o#onComplete());
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

let complete: Utils.supplier(t({..})) = () => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    if (!state#isCancelled()) {
      obs#onComplete();
      state#cancel();
    }
  };  
};

let concatList: Utils.func(list(t({..})), t({..})) = (completableList)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });
    if (!state#isCancelled()) {
      let index = ref(0);
      let max = completableList |> List.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          (completableList->List.nth(index^))#subscribeWith({
            pub onSubscribe = state#link;

            pub onComplete = () => {
              index := index^ + 1;

              if (index^ >= max) {
                obs#onComplete();
              } else {
                sub();
              }
            };

            pub onError = obs#onError;
          }); 
        };

        sub();
      } else {
        obs#onComplete();
        state#cancel();
      }
    }
  };
};

let concatArray: Utils.func(array(t({..})), t({..})) = (completableArray)=> {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });
    if (!state#isCancelled()) {
      let index = ref(0);
      let max = completableArray |> Array.length;
  
      if (max > 0) {
        let rec sub = () => {
          state#unlink();

          (completableArray->Array.get(index^))#subscribeWith({
            pub onSubscribe = state#link;

            pub onComplete = () => {
              index := index^ + 1;

              if (index^ >= max) {
                obs#onComplete();
              } else {
                sub();
              }
            };

            pub onError = obs#onError;
          }); 
        };

        sub();
      } else {
        obs#onComplete();
        state#cancel();
      }
    }
  };
};

let concatWith: Utils.bifunc(t({..}), t({..}), t({..})) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        state#unlink();
        other#subscribeWith({
          pub onSubscribe = state#link;
          pub onComplete = obs#onComplete;
          pub onError = obs#onError;
        });
      };

      pub onError = obs#onError;
    });
  };
};


let defer: Utils.func(Utils.supplier(t({..})), t({..})) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => obs#onError(e);  
  };
};

let delayUntil: Utils.bifunc(t({..}), t({..}), t({..})) = (other, source) => {
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

let doAfterTerminate: Utils.bifunc(Utils.action, t({..}), t({..})) = (onTerminate, source) => {
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

let doFinally: Utils.bifunc(Utils.action, t({..}), t({..})) = (onFinally, source) => {
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

let doOnCancel: Utils.bifunc(Utils.action, t({..}), t({..})) = (onCancel, source) => {
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

let doOnError: Utils.bifunc(Utils.consumer(exn), t({..}), t({..})) = (onError, source) => {
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

let doOnEvent: Utils.bifunc(Utils.consumer(Utils.option(exn)), t({..}), t({..})) = (onEvent, source) => {
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

let doOnSubscribe: Utils.bifunc(Utils.consumer(subscription), t({..}), t({..})) = (onSubscribe, source) => {
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

let doOnComplete: Utils.bifunc(Utils.action, t({..}), t({..})) = (onComplete, source) => {
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

let doOnTerminate: Utils.bifunc(Utils.action, t({..}), t({..})) = (onTerminate, source) => {
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

let error: Utils.func(exn, t({..})) = (err) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      obs#onError(err);
      state#cancel();
    }
  };
};

let fromAction: Utils.func(Utils.action, t({..})) = (action) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (action()) {
        | () => obs#onComplete()
        | exception e => obs#onError(e)
      };

      state#cancel();
    }
  };
};

let fromSupplier: Utils.func(Utils.supplier('a), t({..})) = (supplier) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe(state);

    if (!state#isCancelled()) {
      switch (supplier()) {
        | item => obs#onComplete()
        | exception e => obs#onError(e)
      };

      state#cancel();
    }
  };
};

let fromSingle: Utils.func(Single.t({..}, 'a), t({..})) = (single) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    single#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => obs#onComplete();
      pub onError = obs#onError;
    })
  };
};

let make: Utils.func(Utils.consumer(emitter({..})), t({..})) = (onSubscribe) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    let e = {
      pub setCancellable = state#link;
  
      pub isCancelled = () => state#isCancelled();
    
      pub onComplete = () => {
        if (!state#isCancelled()) {
          obs#onComplete();
          state#cancel();
        }
      };
  
      pub onError = (x) => {
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

let retry: Utils.func(t({..}), t({..})) = (source) => {
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

        pub onComplete = obs#onComplete;

        pub onError = (x) => {
          sub();
        };
      });
    };

    sub();
  };
};

let retryCount: Utils.bifunc(int, t({..}), t({..})) = (count, source) => {
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

        pub onComplete = obs#onComplete;

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

let retryWhile: Utils.bifunc(Utils.bipredicate(int, exn), t({..}), t({..})) = (checker, source) => {
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

        pub onComplete = obs#onComplete;

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

let subscribeOn: Utils.bifunc(Scheduler.t, t({..}), t({..})) = (scheduler, source) => {
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
  
        pub onComplete = obs#onComplete;

        pub onError = obs#onError;
      });
    }));
  };
};

let takeUntil: Utils.bifunc(t({..}), t({..}), t({..})) = (other, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Composite.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    other#subscribeWith({
      pub onSubscribe = state#add;

      pub onComplete = () => {
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

      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };

      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let timer: Utils.bifunc(int, Scheduler.t, t({..})) = (time, scheduler) => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe(scheduler#timeout(() => {
      obs#onComplete();
    }, time));
  }
};

let timeout: Utils.trifunc(int, Scheduler.t, t({..}), t({..})) = (time, scheduler, source) => {
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
      
      pub onComplete = () => {
        obs#onComplete();
        state#cancel();
      };
      
      pub onError = (x) => {
        obs#onError(x);
        state#cancel();
      };
    });
  };
};

let unsubscribeOn: Utils.bifunc(Scheduler.t, t({..}), t({..})) = (scheduler, source) => {
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

      pub onComplete = obs#onComplete;

      pub onError = obs#onError;
    });
  };
};

type basicObserver = {
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
};

let subscribe: Utils.bifunc(basicObserver, t({..}), subscription) = (obs, source) => {
  let state = Cancellable.Linked.make();

  source#subscribeWith({
    pub onSubscribe = state#link;

    pub onComplete = obs.onComplete;

    pub onError = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};