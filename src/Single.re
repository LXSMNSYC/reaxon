type subscription = {
  .
  isCancelled: Utils.producer(bool),
  cancel: Utils.action,
};

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
  isCancelled: Utils.producer(bool),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'emitter;

let ambList = (singleList) => {
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

let ambArray = (singleArray) => {
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

let ambWith = (a, b) => {
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

let cache = (source) => {
  val cached: ref(bool) = ref(false);
  val subscribed: ref(bool) = ref(false);
  val observers: ref(list(observer({..}, 'a))) = ref([]);
  val success = ref(None);
  val error = ref(None);

  pub subscribeWith = (obs) => {

    if (cached^) {
      let state = Cancellable.Boolean.make();

      obs#onSubscribe({
        pub isCancelled = state#isCancelled;
        pub cancel = state#cancel;
      });

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
          pub onSubscribe = sub => {};
  
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

let contains = (item, comparer, source) => {
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
          | None => ()
        };
        state#cancel();
      };

      pub onError = obs#onError;
    })
  };
};

let defer = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => obs#onError(e);  
  };
};

let delayUntil = (other, source) => {
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
}

let doAfterSuccess = (onSuccess, source) => {
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

let doAfterTerminate = (onTerminate, source) => {
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

let doFinally = (onFinally, source) => {
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

let doOnCancel = (onCancel, source) => {
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

let doOnError = (onError, source) => {
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

let doOnEvent = (onEvent, source) => {
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

let doOnSubscribe = (onSubscribe, source) => {
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

let doOnSuccess = (onSuccess, source) => {
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

let doOnTerminate = (onTerminate, source) => {
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

let equals = (a, b) => {
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

let error = (err) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    if (!state#isCancelled()) {
      obs#onError(err);
    }
  };
};

let flatMap = (mapper, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onSuccess = (x) => {
        state#unlink();
        switch(mapper(x)) {
          | item => item#subscribeWith({
            pub onSubscribe = state#link;

            pub onSuccess = obs#onSuccess;

            pub onError = obs#onError;
          }) 
          | exception e => obs#onError(e)
        }
      };

      pub onError = obs#onError;
    });
    
  };
};

let fromProducer = (producer) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    if (!state#isCancelled()) {
      switch (producer()) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e)
      };
      state#cancel();
    }
  };
};

let hide = (source) => {
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
    })
  };
};

let just = (value) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Boolean.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    if (!state#isCancelled()) {
      obs#onSuccess(value);
      state#cancel();
    }
  };
};

let lift = (operator, source) => {
  pub subscribeWith = (obs) => {
    switch(operator(obs)) {
      | newObserver => source#subscribeWith(newObserver)
      | exception e => obs#onError(e) 
    };
  };
}

let make = (onSubscribe) => {
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

let map = (mapper, source) => {
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

let never = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => {};
    });
  };
};

let observeOn = (scheduler, source) => {
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

type basicObserver('a) = {
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
};

let subscribe = (obs, source) => {
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