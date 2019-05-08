/**
 * Represents the structure of a Cancellable object
 */
type t('a) = {
  ..
  cancel: Utils.action,
  isCancelled: Utils.factory(bool),
  addListener: Utils.consumer(Utils.action),
  removeListener: Utils.consumer(Utils.action),
} as 'a;
/**
 * A Boolean Cancellable is a fundamental Cancellable: it represents
 * a boolean state for cancellation.
 */
module Boolean {
  /**
   * Creates a Boolean Cancellable
   */
  let make : Utils.factory(t('a)) = () => {
    /**
     * Holds all event listeners
     */
    val listeners = ref([]);
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
    pub cancel: Utils.action =  () => {
      if(!flag^) {
        listeners^ |> List.iter(x => x());
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled: Utils.factory(bool) = () => flag^;

    /**
     * Add a cancellation event listener
     */
    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    /**
     * Remove a cancellation event listener
     */
    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  } 
}
/**
 * A Composite Cancellable allows combination of multiple Cancellable
 * instances into a single Cancellable
 */
module Composite {
  /**
   * Tells the structure of a Composite Cancellable
   */
  type i('a) = {
    .
    cancel: Utils.action,
    isCancelled: Utils.factory(bool),
    addListener: Utils.consumer(Utils.action),
    removeListener: Utils.consumer(Utils.action),
    add: Utils.consumer(t('a)),
    remove: Utils.consumer(t('a)),
  };
  /**
   * Creates a Composite Cancellable
   */
  let make : Utils.factory(t(i('a))) = () => {
    /**
     * Holds all event listeners
     */
    val listeners = ref([]);
    /**
     * Holds all Cancellable instances
     */
    val container = ref([]);
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
    pub cancel: Utils.action = () => {
      if (!flag^) {
        container^ |> List.iter(x => x#cancel())
        listeners^ |> List.iter(x => x());
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled: Utils.factory(bool) = () => flag^;

    /**
     * Adds a Cancellable instance to the container.
     * 
     * If this Cancellable is already cancelled, the given
     * Cancellable is cancelled as well.
     */
    pub add: Utils.consumer(t('a)) = (c) => {
      if (flag^) {
        c#cancel();
      } else {
        container := [c] @ container^;
      }
    };

    /**
     * Removes a Cancellable instance from the container
     */
    pub remove: Utils.consumer(t('a)) = (c) => {
      if (!flag^) {
        container := container^ |> List.filter(x => x != c);
      }
    };

    /**
     * Add a cancellation event listener
     */
    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    /**
     * Remove a cancellation event listener
     */
    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  };
}
/**
 * A Linked Cancellable allows sharing states with another Cancellable instance.
 */
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
    /**
     * Holds all event listeners
     */
    val listeners = ref([]);
    /**
     * References the listener registered to the linked Cancellable
     */
    val listener = ref(None);
    /**
     * References the linked Cancellable
     */
    val linked = ref(None);
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
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

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled: Utils.factory(bool) = () => flag^;

    /**
     * Unlinks this Cancellable to its linked Cancellable
     */
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

    /**
     * Links this Cancellable to another Cancellable.
     * 
     * If this Cancellable is already cancelled, the other
     * Cancellable is also cancelled, vice-versa.
     */
    pub link: Utils.consumer(t('a)) = (c) => {
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
    };
    

    /**
     * Add a cancellation event listener
     */
    pub addListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := [fn] @ listeners^;
      }
    };

    /**
     * Remove a cancellation event listener
     */
    pub removeListener: Utils.consumer(Utils.action) = (fn: Utils.action) => {
      if (!flag^) {
        listeners := listeners^ |> List.filter(x => x != fn);
      }
    };
  }
}