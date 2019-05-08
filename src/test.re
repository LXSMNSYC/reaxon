let a = Cancellable.Boolean.make();
let b = Cancellable.Boolean.make();

let c = Cancellable.Composite.make();

Js.log(a#isCancelled());
Js.log(b#isCancelled());
Js.log(c#isCancelled());

c#add(a);
c#add(b);

c#cancel();

Js.log(a#isCancelled());
Js.log(b#isCancelled());
Js.log(c#isCancelled());
