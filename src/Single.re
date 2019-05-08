type subscription = {
  .
  isCancelled: Utils.factory(bool),
  cancel: Utils.action,
};

type observer('a) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onSuccess: Utils.consumer('a),
  onError: Utils.consumer(exn),
} as 'a;


type t('a) = {
  .
  subscribe: Utils.consumer(observer('a))
};

type emitter('b) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t('a)),
  isCancelled: Utils.factory(bool),
  onSuccess: Utils.consumer('b),
  onError: Utils.consumer(exn),
} as 'b;

let make: Utils.func(Utils.consumer(emitter('c)), t('c)) = (onSubscribe) => {
  pub subscribe : Utils.consumer(observer('c)) = (obs) => {
    let e : fixedEmitter = {
      val state = ref(Cancellable.Boolean.make());
    
      pub setCancellable: Utils.consumer(Cancellable.t('a)) = (cancellable) => {
        if ((state^)#isCancelled()) {
          cancellable#cancel();
        } else if (cancellable#isCancelled()) {
          (state^)#cancel();
        } else {
          let prev = state^;
          state := cancellable;
          prev#cancel();
        }
      };
  
      pub isCancelled: Utils.factory(bool) = () => (state^)#isCancelled();
    
      pub onSuccess: Utils.consumer('c) = (x: 'c) => {
        if (!(state^)#isCancelled()) {
          obs#onSuccess(x);
          (state^)#cancel();
        }
      };
  
      pub onError: Utils.consumer(exn) = (x: exn) => {
        if (!(state^)#isCancelled()) {
          obs#onError(x);
          (state^)#cancel();
        }
      };
    };
    onSubscribe(e);
  };
};