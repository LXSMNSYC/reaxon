
let operator: Utils.supplier(SingleTypes.operator({..}, 'a)) = () => {
  pub subscribeWith = (obs) => obs#onSubscribe({
    pub isCancelled = () => false;
    pub cancel = () => ();
  });
};