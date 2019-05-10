[@bs.val] external setTimeout : (unit => unit) => int => unit = "setTimeout";

let instantScheduler: Scheduler.t = {
  pub run = (fn) => {
    let state = Cancellable.Boolean.make();
    fn();
    state#cancel();
    state;
  };

  pub timeout = (fn, time) => {
    let state = Cancellable.Boolean.make();

    setTimeout(() => {
      if (!state#isCancelled()) {
        fn();
      }
    }, time);

    state;
  };
};

Completable.fromSupplier(() => {
  Js.log("Hello World");
  100
})
  |> Completable.subscribe({
    onComplete: () => Js.log("Completed"),
    onError: Js.log,
  });