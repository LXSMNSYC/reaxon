
let operator: Utils.supplier(SingleTypes.t({..}, 'a)) = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};