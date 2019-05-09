let a = Single.just("Hello world");

a |> Single.subscribe({
  onSuccess: Js.log,
  onError: Js.log,
});