/**
 * Represents the one-to-one lifecycle of an Observer to an Observable.
 * 
 * It can only be used once by a single Observer.
 * 
 * It is used to cancel demand and allow resource cleanup.
 */
module Subscription {
  type t = {
    cancel: unit => unit,
  };
}

module Single {
  module Observer {
    type t('a) = {
      onSubscribe: Subscription.t => unit,
      onSuccess: 'a => unit,
      onError: exn => unit,
    };

    module Lambda {
      type t('a) = {
        onSuccess: 'a => unit,
        onError: exn => unit,
      };
    }
  }

  module Emitter {
    type t('a) = {
      setSubscription: Subscription.t => unit,
      isCancelled: unit => bool,
      onSuccess: 'a => unit,
      onError: exn => unit,
    };
  }


  module Notification {
    type t('a) =
      | OnSuccess('a)
      | OnError(exn)
    ;
  }

  type t('a) = {
    subscribeWith: Observer.t('a) => unit
  };
}


module Completable {
  module Observer {
    type t = {
      onSubscribe: Subscription.t => unit,
      onComplete: unit => unit,
      onError: exn => unit,
    };

    module Lambda {
      type t = {
        onComplete: unit => unit,
        onError: exn => unit,
      };
    }
  }

  module Emitter {
    type t = {
      setSubscription: Subscription.t => unit,
      isCancelled: unit => bool,
      onComplete: unit => unit,
      onError: exn => unit,
    };
  }

  module Notification {
    type t = 
      | OnComplete
      | OnError(exn)
    ;
  }

  type t = {
    subscribeWith: Observer.t => unit
  };
}

module Maybe {
  module Observer {
    type t('a) = {
      onSubscribe: Subscription.t => unit,
      onComplete: unit => unit,
      onSuccess: 'a => unit,
      onError: exn => unit,
    };

    module Lambda {
      type t('a) = {
        onComplete: unit => unit,
        onSuccess: 'a => unit,
        onError: exn => unit,
      };
    }
  }

  module Emitter {
    type t('a) = {
      setSubscription: Subscription.t => unit,
      isCancelled: unit => bool,
      onComplete: unit => unit,
      onSuccess: 'a => unit,
      onError: exn => unit,
    };
  }

  module Notification {
    type t('a) =
      | OnSuccess('a)
      | OnError(exn)
      | OnComplete
    ;
  }

  type t('a) = {
    subscribeWith: Observer.t('a) => unit
  };
}

module Observable {
  module Observer {
    type t('a) = {
      onSubscribe: Subscription.t => unit,
      onComplete: unit => unit,
      onError: exn => unit,
      onNext: 'a => unit,
    };

    module Lambda {
      type t('a) = {
        onComplete: unit => unit,
        onError: exn => unit,
        onNext: 'a => unit,
      };
    }
  }

  module Emitter {
    type t('a) = {
      setSubscription: Subscription.t => unit,
      isCancelled: unit => bool,
      onComplete: unit => unit,
      onError: exn => unit,
      onNext: 'a => unit,
    };
  }

  module Notification {
    type t('a) =
      | OnError(exn)
      | OnComplete
      | OnNext('a)
    ;
  }

  type t('a) = {
    subscribeWith: Observer.t('a) => unit
  };
}

module Scheduler {
  type t = {
    run: (unit => unit) => Subscription.t,
    timeout: (unit => unit) => int => Subscription.t,
  };
}