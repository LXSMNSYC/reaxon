open Single;

let a = Single.make((e) => {
  Js.log("This");
  Js.log("is");
  Js.log("cached");
  e#onSuccess("Hello World");
});

let cached = a |> Single.cache;

cached |> Single.subscribe({
  onSuccess: Js.log,
  onError: Js.log,
});

cached |> Single.subscribe({
  onSuccess: Js.log,
  onError: Js.log,
});