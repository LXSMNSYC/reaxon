exception MyError;

let a = Single.just("Hello World");

a |> Single.flatMap(x => Single.just(x ++ " World"))
|> Single.subscribe({
  onSuccess: Js.log,
  onError: Js.log,
})