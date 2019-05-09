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

Single.just("Hello World")
  |> Single.delay(1000, instantScheduler)
  |> Single.subscribe({
    onSuccess: Js.log,
    onError: Js.log,
  });