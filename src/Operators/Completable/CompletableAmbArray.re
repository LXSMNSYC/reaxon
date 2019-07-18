/**
 * @license
 * MIT License
 *
 * Copyright (c) 2019 Alexis Munsayac
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * @author Alexis Munsayac <alexis.munsayac@gmail.com>
 * @copyright Alexis Munsayac 2019
 */
let operator = (sources: array(Types.Completable.t)): Types.Completable.t => {
  subscribeWith: (obs: Types.Completable.Observer.t) => {
    let finished = ref(false);
    let subRef: ref(list(Types.Subscription.t)) = ref([]);
  
    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!finished^) {
          subRef^ |> List.iter((item: Types.Subscription.t) => item.cancel());
          finished := true;
        }
      }
    };

    sources |> Array.iter((source: Types.Completable.t) => {
      let subscribed = ref(false);
      source.subscribeWith({
        onSubscribe: (sub: Types.Subscription.t) => {
          if (finished^ || subscribed^) {
            sub.cancel();
          } else {
            subRef := [sub] @ subRef^;
            subscribed := true;
          }
        },
        onComplete: () => {
          if (!finished^) {
            obs.onComplete();
            subscription.cancel();
          }
        },
        onError: (x: exn) => {
          if (!finished^) {
            obs.onError(x);
            subscription.cancel();
          } else {
            raise(x);
          }
        },
      });
    });
  }
};