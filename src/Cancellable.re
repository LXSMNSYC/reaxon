/**
 * Represents the structure of a Cancellable object
 */
type t('a) = {
  ..
  cancel: Utils.action,
  isCancelled: Utils.producer(bool),
} as 'a;

/**
 * A Boolean Cancellable is a fundamental Cancellable: it represents
 * a boolean state for cancellation.
 */
module Boolean {
  type i = t({
    .
    cancel: Utils.action,
    isCancelled: Utils.producer(bool),
  });
  /**
   * Creates a Boolean Cancellable
   */
  let make : Utils.producer(i) = () => {
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
    pub cancel: Utils.action =  () => {
      if(!flag^) {
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled: Utils.producer(bool) = () => flag^;
  } 
}
/**
 * A Composite Cancellable allows combination of multiple Cancellable
 * instances into a single Cancellable
 */
module Composite {
  /**
   * Creates a Composite Cancellable
   */
  let make : Utils.producer(t({..})) = () => {
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
    pub isCancelled: Utils.producer(bool) = () => flag^;

    /**
     * Adds a Cancellable instance to the container.
     * 
     * If this Cancellable is already cancelled, the given
     * Cancellable is cancelled as well.
     */
    pub add: Utils.consumer(t({..})) = (c) => {
      if (flag^) {
        c#cancel();
      } else {
        container := [c] @ container^;
      }
    };

    /**
     * Removes a Cancellable instance from the container
     */
    pub remove: Utils.consumer(t({..})) = (c) => {
      if (!flag^) {
        container := container^ |> List.filter(x => x != c);
      }
    };
  };
}
/**
 * A Linked Cancellable allows sharing states with another Cancellable instance.
 */
module Linked {
  let make : Utils.producer(t({..})) = () => {
    /**
     * References the listener registered to the linked Cancellable
     */
    val listener = ref(None);
    /**
     * References the linked Cancellables
     */
    val next = ref(None);
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
    pub cancel: Utils.action = () => {
      if (!flag^) {
        switch (next^) {
          | Some(c) => {
            next := None;
            c#cancel();
          }
          | None => ()
        };
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled: Utils.producer(bool) = () => flag^;

    /**
     * Unlinks this Cancellable to its linked Cancellable
     */
    pub unlink: Utils.action = () => {
      if (!flag^ && next^ != None) {
        next := None;
      }
    };

    /**
     * Links this Cancellable to another Cancellable.
     * 
     * If this Cancellable is already cancelled, the other
     * Cancellable is also cancelled, vice-versa.
     */
    pub link: Utils.consumer(t({..})) = (c) => {
      if (c#isCancelled()) {
        this#cancel();
      } else if (flag^) {
        c#cancel();
      } else {
        let source = this;
        next := Some({
          pub isCancelled = c#isCancelled;

          pub cancel = () => {
            source#cancel();
            c#cancel();
          };
        })
      }
    };
  }
}