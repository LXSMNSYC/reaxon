
let operator: Utils.supplier(MaybeTypes.operator({..}, 'a)) = () => {
  pub subscribeWith = (obs) => {
    obs#onSubscribe({
      pub isCancelled = () => false;
      pub cancel = () => ();
    });
  };
};