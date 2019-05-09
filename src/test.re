let a = Completable.make((e) => {
  Js.log("Hello");
  e#onComplete();
});

let b = Completable.make((e) => {
  Js.log("World");
  e#onComplete();
});

a |> Completable.concatWith(b) |> Completable.subscribe({
  onComplete: () => Js.log("Completed!"),
  onError: Js.log,
});