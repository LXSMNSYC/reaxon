type t = {
  subscription: Types.Subscription.t,
  container: ref(list(Types.Subscription.t)),
  alive: unit => bool,
  add: Types.Subscription.t => unit,
  remove: Types.Subscription.t => unit,
}

let make = (): t => {
  let alive = ref(true);
  let container = ref([]);

  {
    container,
    subscription: {
      cancel: () => {
        if (alive^) {
          container^ |> List.iter((sub: Types.Subscription.t) => sub.cancel());
        }
      },
    },
    alive: () => alive^,
    add: (sub) => {
      if (alive^) {
        container := [sub] @ container^;
      } else {
        sub.cancel();
      }
    },
    remove: (sub) => {
      if (alive^) {
        container := container^ |> List.filter(x => x != sub);
      }
    }
  }
};