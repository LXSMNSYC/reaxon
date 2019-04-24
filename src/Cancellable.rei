type cancelState;
type cancellable;

let make : unit => cancellable;

let cancel : cancellable => unit;
let cancelled : cancellable => bool;

let add : cancellable => cancellable => unit;
let remove : cancellable => cancellable => unit;

let link : cancellable => cancellable => unit;
let unlink : cancellable => unit;

let addListener : (unit => unit) => cancellable => unit;
let removeListener : (unit => unit) => cancellable => unit;