type t('t) = {
  ..
  cancel: unit => unit
} as 't;

type s = t({
  .
  cancel: unit => unit
});

module Composite {
  let make = () => {
    val state = ref(false);
    val subs = ref([]);

    pub add = (n: t('a)) =>
      if (state^) {
        n#cancel();
      } else {
        subs := [n] @ subs^;
      };

    pub cancel = () => {
      if (!state^) {
        subs^ |> List.iter(x => x#cancel());
        subs := [];
        state := true;
      }
    };
  };
}