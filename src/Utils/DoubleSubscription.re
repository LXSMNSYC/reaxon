let make = () => {
  let alive = ref(true);

  let outerRef: ref(option(Types.Subscription.t)) = ref(None);
  let innerRef: ref(option(Types.Subscription.t)) = ref(None);

  let subscription: Types.Subscription.t = {
    cancel: () => {
      if (alive^) {
        OptionalSubscription.cancel(outerRef^);
        OptionalSubscription.cancel(innerRef^);
        alive := false;
      }
    }
  };

  (alive, outerRef, innerRef, subscription);
};
