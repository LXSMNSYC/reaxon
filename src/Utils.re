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
  pub cancel = c#cancel;
};