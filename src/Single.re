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

let defer: Utils.func(Utils.producer(t({..}, 'a)), t({..}, 'a)) = (supplier) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => switch (supplier()) {
    | source => source#subscribeWith(obs)
    | exception e => obs#onError(e);  
  };
};

let doAfterSuccess: Utils.bifunc(Utils.consumer('a), t({..}, 'a), t({..}, 'a)) = (onSuccess, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {

    source#subscribeWith({
      val state = Cancellable.Linked.make();
  
      pub onSubscribe: Utils.consumer(subscription) = state#link;
  
      pub onSuccess: Utils.consumer('a) = (x) => {
        obs#onSuccess(x);
        onSuccess(x);
      };
  
      pub onError: Utils.consumer(exn) = obs#onError;
    });
  };
};

let doAfterTerminate: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onTerminate, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {

    source#subscribeWith({
      val state = Cancellable.Linked.make();
  
      pub onSubscribe: Utils.consumer(subscription) = state#link;
  
      pub onSuccess: Utils.consumer('a) = (x) => {
        obs#onSuccess(x);
        onTerminate();
      };
  
      pub onError: Utils.consumer(exn)  = (x) => {
        obs#onError(x);
        onTerminate();
      };
    });
  };
};

let doFinally: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onFinally, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {

    source#subscribeWith({
      val state = Cancellable.Linked.make();
  
      pub onSubscribe: Utils.consumer(subscription) = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            sub#cancel();
            onFinally();
          }
        });
      };
  
      pub onSuccess: Utils.consumer('a) = (x) => {
        obs#onSuccess(x);
        onFinally();
      };
  
      pub onError: Utils.consumer(exn)  = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
  };
};

let doOnCancel: Utils.bifunc(Utils.action, t({..}, 'a), t({..}, 'a)) = (onCancel, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {

    source#subscribeWith({
      val state = Cancellable.Linked.make();
  
      pub onSubscribe: Utils.consumer(subscription) = (sub) => {
        state#link({
          pub isCancelled = sub#isCancelled;
          pub cancel = () => {
            onCancel();
            sub#cancel();
          }
        });
      };
  
      pub onSuccess: Utils.consumer('a) = obs#onSuccess;
  
      pub onError: Utils.consumer(exn) = obs#onError;
    });
  };
};

let doOnError: Utils.bifunc(Utils.consumer(exn), t({..}, 'a), t({..}, 'a)) = (onError, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {
    let state = Cancellable.Linked.make();
    source#subscribeWith({
      pub onSubscribe: Utils.consumer(subscription) = state#link;
  
      pub onSuccess: Utils.consumer('a) = obs#onSuccess;
  
      pub onError: Utils.consumer(exn) = (x) => {
        onError(x);
        obs#onError(x);
      };
    });
  };
};

let doOnEvent: Utils.bifunc(Utils.biconsumer(option('a), option(exn)), t({..}, 'a), t({..}, 'a)) = (onEvent, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {
    let state = Cancellable.Linked.make();
    source#subscribeWith({
      pub onSubscribe: Utils.consumer(subscription) = state#link;
  
      pub onSuccess: Utils.consumer('a) = (x) => {
        onEvent(Some(x), None);
        obs#onSuccess(x);
      };
  
      pub onError: Utils.consumer(exn) = (x) => {
        onEvent(None, Some(x));
        obs#onError(x);
      };
    });
  };
};

let doOnSubscribe: Utils.bifunc(Utils.consumer(subscription), t({..}, 'a), t({..}, 'a)) = (onSubscribe, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {
    let state = Cancellable.Linked.make();
    source#subscribeWith({
      pub onSubscribe: Utils.consumer(subscription) = (sub) => {
        onSubscribe(sub);
        state#link(sub);
      };

      pub onSuccess: Utils.consumer('a) = obs#onSuccess;

      pub onError: Utils.consumer(exn) = obs#onError;
    });
  };
};


let make: Utils.func(Utils.consumer(emitter({..}, 'a)), t({..}, 'a)) = (onSubscribe) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {
    let state = Cancellable.Linked.make();

    let e = {
      pub setCancellable: Utils.consumer(Cancellable.t({..})) = state#link;
  
      pub isCancelled: Utils.producer(bool) = () => state#isCancelled();
    
      pub onSuccess: Utils.consumer('a) = (x: 'a) => {
        if (!state#isCancelled()) {
          obs#onSuccess(x);
          state#cancel();
        }
      };
  
      pub onError: Utils.consumer(exn) = (x: exn) => {
        if (!state#isCancelled()) {
          obs#onError(x);
          state#cancel();
        }
      };
    };

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    try(onSubscribe(e)) {
      | err => {
        obs#onError(err);
        state#cancel();
      } 
    };
  };
};

let map: Utils.bifunc(Utils.func('a, 'a), t({..}, 'a), t({..}, 'a)) = (mapper, source) => {
  pub subscribeWith: Utils.consumer(observer({..}, 'a)) = (obs) => {
    let state = Cancellable.Linked.make();
    source#subscribeWith({
      pub onSubscribe: Utils.consumer(subscription) = state#link;

      pub onSuccess: Utils.consumer('a) = (x) => switch(mapper(x)) {
        | item => obs#onSuccess(item)
        | exception e => obs#onError(e) 
      };

      pub onError: Utils.consumer(exn) = obs#onError;
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
    pub onSubscribe: Utils.consumer(subscription) = state#link;

    pub onSuccess: Utils.consumer('a) = obs.onSuccess;

    pub onError: Utils.consumer(exn) = obs.onError;
  });
  {
    pub isCancelled = state#isCancelled;
    pub cancel = state#cancel;
  }
};