let a: Single.t({
  .
  onSuccess: Utils.consumer(string),
  onError: Utils.consumer(exn),
}, string) = Single.just("Hello world");

a |> Single.subscribe({
  onSuccess: Js.log,
  onError: Js.log,
});