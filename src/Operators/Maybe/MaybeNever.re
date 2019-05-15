let instance = {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};

let operator: unit => MaybeTypes.operator('downstream, 'a) = () => instance;
