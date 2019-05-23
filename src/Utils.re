let fromOptionArray = opt => {
  let result = ref([||]);

  opt |> Array.iter(x => 
    switch (x) {
      | Some(item) => {
        result := Array.append(result^, [|item|]);
      }
      | None => ()
    }
  );

  result^;
};

let c2sub = c => {
  pub isCancelled = c#isCancelled;
  pub cancel = c#cancel;
};