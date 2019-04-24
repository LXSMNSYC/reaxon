type cancelState;
type t;

let make : unit => t;

let cancel : t => unit;
let cancelled : t => bool;

let add : t => t => unit;
let remove : t => t => unit;

let link : t => t => unit;
let unlink : t => unit;

let addListener : (unit => unit) => t => unit;
let removeListener : (unit => unit) => t => unit;