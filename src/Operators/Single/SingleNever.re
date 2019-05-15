let instance = {
  pub subscribeWith = (obs) => obs#onSubscribe({
    pub isCancelled = () => false;
    pub cancel = () => ();
  });
};

let operator: unit => SingleTypes.operator('downstream, 'a) = () => instance;