type t = {
  .
  run: Utils.func(Utils.action, Cancellable.t({.
    isCancelled: Utils.producer(bool),
    cancel: Utils.action,
  }))
};