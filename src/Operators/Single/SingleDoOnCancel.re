let operator = (onCancel, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = (state) => obs#onSubscribe({
        val cancelled = ref(false);
        pub cancel = () => 
          if (!cancelled^) {
            onCancel();
            state#cancel();
            cancelled := true;
          }
      });

      pub onSuccess = obs#onSuccess;
      pub onError = obs#onError;
    });
};