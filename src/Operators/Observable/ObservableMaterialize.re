let operator: ObservableTypes.t('source, 'upstream, 'a) => ObservableTypes.operator('downstream, Notification.Observable.t('a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe({
      pub isCancelled = state#isCancelled;
      pub cancel = state#cancel;
    });

    source#subscribeWith({
      pub onSubscribe = state#link;

      pub onComplete = () => {
        obs#onNext(Notification.Observable.OnComplete);
        obs#onComplete();
      };

      pub onError = x => {
        obs#onNext(Notification.Observable.OnError(x));
        obs#onComplete();
      };

      pub onNext = x => obs#onNext(Notification.Observable.OnNext(x));
    });
  };
};