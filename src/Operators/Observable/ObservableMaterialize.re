let operator: ObservableTypes.s('source, 'a) => ObservableTypes.operator('downstream, Notification.Observable.t('a)) = (source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

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