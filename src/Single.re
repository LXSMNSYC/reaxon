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

type t('b,'a) = {
  .
  subscribeWith: Utils.consumer(observer('b, 'a)),
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
    }))
;
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

let defer: Utils.func(Utils.producer(t({..}, 'a)), t({..}, 'a)) = (supplier) => {
  pub subscribeWith = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => obs#onError(e);  
  };
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

let doOnEvent: Utils.bifunc(Utils.biconsumer(option('a), option(exn)), t({..}, 'a), t({..}, 'a)) = (onEvent, source) => {
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

let doOnSuccess: Utils.bifunc(Utils.consumer(subscription), t({..}, 'a), t({..}, 'a)) = (onSuccess, source) => {
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

let error: Utils.func(exn, t({..}, 'a)) = (err) => {
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

let flatMap: Utils.bifunc(Utils.func('a, t({..}, 'a)), t({..}, 'a), t({..}, 'a)) = (mapper, source) => {
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

let fromProducer: Utils.func(Utils.producer('a), t({..}, 'a)) = (producer) => {
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
    })
  };
};

let just: Utils.func('a, t({..}, 'a)) = (value) => {
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

let map: Utils.bifunc(Utils.func('a, 'a), t({..}, 'a), t({..}, 'a)) = (mapper, source) => {
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