type t = {
  .
  run: Utils.func(Utils.action, Cancellable.t({.
    isCancelled: Utils.supplier(bool),
    cancel: Utils.action,
  })),

  timeout: Utils.bifunc(Utils.action, int, Cancellable.t({.
    isCancelled: Utils.supplier(bool),
    cancel: Utils.action,
  })),
};