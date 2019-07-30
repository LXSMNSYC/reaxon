
let rec forEach = (initial, condition, block) => {
  if (condition(initial)) {
    forEach(block(initial), condition, block);
  } else {
    initial;
  }
};

let signal = Single.make((emitter) => {
  emitter.onSuccess(forEach(0, state => state < 21474836, state => state + 1));
}) |> Single.cache
  |> Single.materialize
  |> Single.dematerialize
  |> Single.map(x => "Success: " ++ string_of_int(x));

signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});
signal |> Single.subscribe({
  onSuccess: x => Js.log(x),
  onError: x => Js.log(x),
});