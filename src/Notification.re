module Completable {
  type t = 
    | OnComplete
    | OnError(exn)
  ;
}

module Single {
  type t('a) =
    | OnSuccess('a)
    | OnError(exn)
  ;
}

module Maybe {
  type t('a) =
    | OnSuccess('a)
    | OnError(exn)
    | OnComplete
  ;
}

module Publisher {
  type t('a) =
    | OnError(exn)
    | OnComplete
    | OnNext('a)
  ;
}

module Observable {
  type t('a) =
    | OnError(exn)
    | OnComplete
    | OnNext('a)
  ;
}