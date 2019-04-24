type cancelState = 
  | CANCELLED
  | UNCANCELLED
  ;
  
type option('a) =
  | Some('a)
  | None
  ;
  
type callable = unit => unit;
  
type cancellable = {
  state: ref(cancelState),
  linked: ref(option(cancellable)),
  listener: ref(option(callable)),
  
  composition: ref(list(cancellable)),
  listeners: ref(list(callable)),
};

let make = () => {
  {
    state: ref(UNCANCELLED),
    linked: ref(None),
    listener: ref(None),
    composition: ref([]),
    listeners: ref([]),
  };
};

let cancelled = (c: cancellable) => c.state^ == CANCELLED;

let addListener = (c: callable, src: cancellable) => {
  if (!cancelled(src)) {
    src.listeners := [c] @ src.listeners^;
  }
};

let removeListener = (c: callable, src: cancellable) => {
  if (!cancelled(src)) {
    src.listeners := src.listeners^ |> List.filter(x => x != c);
  }
};

let unlink = (src: cancellable) => {
  if (!cancelled(src) && src.linked^ != None) {
    switch (src.listener^) {
      | Some(c) => src |> removeListener(c);
      | None => ()
    };
    
    src.linked := None;
    src.listener := None;
  }
};

let rec cancel = (src: cancellable) => {
  if (!cancelled(src)) {
    switch(src.linked^) {
      | Some(linked) => {
        unlink(src);
        cancel(linked);
      }
      | None => ()
    };

    src.state := CANCELLED;
    src.composition^ |> List.iter(x => cancel(x));
    src.listeners^ |> List.iter(x => x());
  }
}

let link = (c: cancellable, src: cancellable) => {
  if (c !== src) {
    if (cancelled(c)) {
      cancel(src);
    } else if (cancelled(src)) {
      cancel(c);
    } else {
      unlink(src);
      src.linked := Some(c);
      
      let listener = () => cancel(c);
      
      src.listener := Some(listener);
      c |> addListener(listener);
    }
  }
};

let add = (c: cancellable, src: cancellable) => {
  if (cancelled(src)) {
    cancel(c);
  } else {
    src.composition := [c] @ src.composition^;
  }
};

let remove = (c: cancellable, src: cancellable) => {
  if (!cancelled(src)) {
    src.composition := src.composition^ |> List.filter(x => x != c);
  }
};