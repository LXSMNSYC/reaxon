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

Single.just(Single.just("Hello"))
  |> Single.merge
  |> Single.subscribeOn(jsTimeoutScheduler)
  |> Single.subscribe({
    onSuccess: Js.log,
    onError: Js.log,
  });

Js.log("Hello World");