type t('a) = {
  ..
  cancel: Functions.action,
  isCancelled: Functions.factory(bool),
} as 'a;


module Boolean {
  let make = () => {
    val flag = ref(false);

    pub cancel =  () => {
      flag := true;
    };

    pub isCancelled = () => flag^;
  } 
}

module Composite {
  let make = () => {
    val container : ref(list(t('a))) = ref([]);
    val flag = ref(false);

    pub cancel = () => {
      if (!flag^) {
        container^ |> List.iter(x => x#cancel())
        flag := true;
      }
    };

    pub isCancelled = () => flag^;

    pub add = (c: t('a)) => {
      if (flag^) {
        c#cancel();
      } else {
        container := [c] @ container^;
      }
    };

    pub remove = (c: t('a)) => {
      if (!flag^) {
        container := container^ |> List.filter(x => x != c);
      }
    };
  };
}