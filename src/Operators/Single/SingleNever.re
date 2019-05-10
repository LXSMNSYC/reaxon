
let operator: Utils.supplier(SingleTypes.t(SingleTypes.observer({..}, 'a), 'a)) = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};