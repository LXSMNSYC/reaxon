let operator = (onFinally, source) => {
  pub subscribeWith = (obs) => 
    Utils.makeCSO(source, {
      pub onSubscribe = (state) => obs#onSubscribe({
        val cancelled = ref(false);
        pub cancel = () => 
          if (!cancelled^) {
            state#cancel();
            onFinally();
            cancelled := true;
          };
      });

      pub onSuccess = (x) => {
        obs#onSuccess(x);
        onFinally();
      };

      pub onError  = (x) => {
        obs#onError(x);
        onFinally();
      };
    });
};