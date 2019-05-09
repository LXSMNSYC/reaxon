type t = {
  .
  run: Utils.func(Utils.action, Cancellable.t({.
    isCancelled: Utils.producer(bool),
    cancel: Utils.action,
  })),

  timeout: Utils.bifunc(Utils.action, int, Cancellable.t({.
    isCancelled: Utils.producer(bool),
    cancel: Utils.action,
  })),
};