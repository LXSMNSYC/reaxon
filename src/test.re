

let print = (msg: string) => {
  Js.log(msg);
};

let call = (consumer: Functions.consumer(string)) => {
  consumer("Hello World");
}

call(print);