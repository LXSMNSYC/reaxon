/**
 * Represents the structure of a Cancellable object
 */
type t('a) = {
  ..
  cancel: unit => unit,
  isCancelled: unit => bool,
} as 'a;

/**
 * A Boolean Cancellable is a fundamental Cancellable: it represents
 * a boolean state for cancellation.
 */
module Boolean {
  type i = t({
    .
    cancel: unit => unit,
    isCancelled: unit => bool,
  });
  /**
   * Creates a Boolean Cancellable
   */
  let make : unit => i = () => {
    /**
     * Represents the state
     */
    val flag = ref(false);

    /**
     * Cancels this Cancellable instance.
     */
    pub cancel =  () => {
      if(!flag^) {
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled = () => flag^;
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
  let make : unit => t({..}) = () => {
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
    pub cancel = () => {
      if (!flag^) {
        container^ |> List.iter(x => x#cancel())
        flag := true;
      }
    };

    /**
     * Checks if this Cancellable instance is cancelled.
     */
    pub isCancelled = () => flag^;

    /**
     * Adds a Cancellable instance to the container.
     * 
     * If this Cancellable is already cancelled, the given
     * Cancellable is cancelled as well.
     */
    pub add: t({..}) => unit = (c) => {
      if (flag^) {
        c#cancel();
      } else {
        container := [c] @ container^;
      }
    };

    /**
     * Removes a Cancellable instance from the container
     */
    pub remove: t({..}) => unit = (c) => {
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
  let make : unit => t({..}) = () => {
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
    pub cancel = () => {
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
    pub isCancelled = () => flag^ || switch (next^) {
      | Some(n) => if (n#isCancelled()) {
        this#cancel();
        true;
      } else {
        false;
      }
      | None => false
    };

    /**
     * Unlinks this Cancellable to its linked Cancellable
     */
    pub unlink: unit => unit = () => {
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
    pub link: t({..}) => unit = (c) => {
      if (c#isCancelled()) {
        this#cancel();
      } else if (flag^) {
        c#cancel();
      } else {
        next := Some(c);
      }
    };
  }
}