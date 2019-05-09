
type subscription = Cancellable.Boolean.i;


type observer('observer) = {
  ..
  onSubscribe: Utils.consumer(subscription),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
} as 'observer;


type t('observer) = {
  .
  subscribeWith: Utils.consumer(observer('observer)),
};


type emitter('emitter) = {
  ..
  setCancellable: Utils.consumer(Cancellable.t({..})),
  isCancelled: Utils.producer(bool),
  onComplete: Utils.action,
  onError: Utils.consumer(exn),
} as 'emitter;


let ambList = (completableList) => {
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



let ambArray = (completableArray) => {
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


let ambWith = (a, b) => {
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