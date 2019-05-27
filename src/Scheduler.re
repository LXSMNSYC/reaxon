type t = {
  .
  run: (unit => unit) => unit,

  timeout: (unit => unit) => int => unit,
};