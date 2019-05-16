type t = {
  .
  run: (unit => unit) => Cancellable.t({.
    isCancelled: unit => bool,
    cancel: unit => unit,
  }),

  timeout: (unit => unit) => int => Cancellable.t({.
    isCancelled: unit => bool,
    cancel: unit => unit,
  }),
};