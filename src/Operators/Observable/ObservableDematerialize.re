let operator: ObservableTypes.s('source, Notification.Observable.t('a)) => ObservableTypes.operator('downstream, 'a) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onNext = x => switch (x) {
        | Notification.Observable.OnComplete => {
          obs#onComplete();
          state#cancel();
        }
        | Notification.Observable.OnError(item) => {
          obs#onError(item)
          state#cancel();
        }
        | Notification.Observable.OnNext(item) => obs#onNext(item)
      };

      pub onComplete = obs#onComplete;
      pub onError = obs#onError;
    });
  };
};