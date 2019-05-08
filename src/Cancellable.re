type t('a) = {
  ..
  cancel: Utils.action,
  isCancelled: Utils.factory(bool),
  addListener: Utils.consumer(Utils.action),
  removeListener: Utils.consumer(Utils.action),
} as 'a;

module Boolean {
  let make : Utils.factory(t('a)) = () => {
    val listeners = ref([]);
    val flag = ref(false);

    pub cancel: Utils.action =  () => {
      if(!flag^) {
        listeners^ |> List.iter(x => x());
        flag := true;
      }
    };

    pub isCancelled: Utils.factory(bool) = () => flag^;

    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  } 
}

module Composite {
  type i('a) = {
    .
    cancel: Utils.action,
    isCancelled: Utils.factory(bool),
    addListener: Utils.consumer(Utils.action),
    removeListener: Utils.consumer(Utils.action),
    add: Utils.consumer(t('a)),
    remove: Utils.consumer(t('a)),
  };
  let make : Utils.factory(t(i('a))) = () => {
    val listeners = ref([]);
    val container = ref([]);
    val flag = ref(false);

    pub cancel: Utils.action = () => {
      if (!flag^) {
        container^ |> List.iter(x => x#cancel())
        listeners^ |> List.iter(x => x());
        flag := true;
      }
    };

    pub isCancelled: Utils.factory(bool) = () => flag^;

    pub add: Utils.consumer(t('a)) = (c) => {
      if (flag^) {
        c#cancel();
      } else {
        container := [c] @ container^;
      }
    };

    pub remove: Utils.consumer(t('a)) = (c) => {
      if (!flag^) {
        container := container^ |> List.filter(x => x != c);
      }
    };

    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  };
}

module Linked {
  type i('a) = {
    .
    cancel: Utils.action,
    isCancelled: Utils.factory(bool),
    addListener: Utils.consumer(Utils.action),
    removeListener: Utils.consumer(Utils.action),
    link: Utils.consumer(t('a)),
    unlink: Utils.action,
  };
  let make : Utils.factory(t(i('a))) = () => {
    val listeners = ref([]);
    val listener = ref(None);
    val linked = ref(None);
    val flag = ref(false);

    pub cancel: Utils.action = () => {
      if (!flag^) {
        switch (linked^) {
          | Some(c) => {
            this#unlink();
            c#cancel();
          }
          | None => ()
        };

        listeners^ |> List.iter(x => x());
        flag := true;
      }
    };

    pub isCancelled: Utils.factory(bool) = () => flag^;

    pub unlink: Utils.action = () => {
      if (!flag^ && linked^ != None) {
        switch (linked^) {
          | Some(c) =>  switch (listener^) {
            | Some(x) => c#removeListener(x)
            | None => ()
          }
          | None => ()
        }

        linked := None;
        listener := None;
      }
    };

    pub link: Utils.consumer(t('a)) = (c) => {
      if (c !== this) {
        if (c#isCancelled()) {
          this#cancel();
        } else if (flag^) {
          c#cancel();
        } else {
          this#unlink();

          linked := Some(c);

          let l = () => this#cancel();
          c#addListener(l);
          listener := Some(l);
        }
      }
    };
    

    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  }
}