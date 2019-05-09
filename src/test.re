let a = Completable.make((e) => {
  Js.log("Hello");
  e#onComplete();
});

let b = Completable.make((e) => {
  Js.log("World");
  e#onComplete();
});

Completable.concatArray([|a, b|]) |> Completable.subscribe({
  onComplete: () => Js.log("Completed!"),
  onError: Js.log,
});