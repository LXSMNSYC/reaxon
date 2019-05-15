[@bs.val] external setTimeout : (unit => unit) => int => unit = "setTimeout";

let jsInstantScheduler: Scheduler.t = {
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

let jsTimeoutScheduler: Scheduler.t = {
  pub run = (fn) => {
    let state = Cancellable.Boolean.make();
    setTimeout(() => {
      fn();
      state#cancel();
    }, 0);
    state;
  };

  pub timeout = (fn, time) => {
    let state = Cancellable.Boolean.make();

    setTimeout(() => {
      setTimeout(() => {
        if (!state#isCancelled()) {
          fn();
        }
      }, time);
    }, 0);

    state;
  };
};

Observable.range(1, 10, 1)
  |> Observable.subscribe({
    onNext: x => Js.log("Next: " ++ string_of_int(x)),
    onError: Js.log,
    onComplete: () => Js.log("Completed"),
  });
Js.log("Hello World");