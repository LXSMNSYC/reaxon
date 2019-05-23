let subscription = {
  pub isCancelled = () => false;
  pub cancel = () => ();
};

let instance = {
  pub subscribeWith = (obs) => obs#onSubscribe(subscription);
};

let operator: unit => SingleTypes.operator('downstream, 'a) = () => instance;
