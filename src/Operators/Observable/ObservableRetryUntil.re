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

let operator = (supplier: int => bool, source: Types.Observable.t('a)): Types.Observable.t('a) => {
  subscribeWith: (obs: Types.Observable.Observer.t('a)) => {
    let subscribed = ref(false);
    let finished = ref(false);
    let subRef: ref(option(Types.Subscription.t)) = ref(None);

    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!finished^) {
          if (subscribed^) {
            switch (subRef^) {
            | Some(ref) => ref.cancel()
            | None => ()
            }
          }
          finished := true;
        }
      }
    };

    let retries = ref(-1);

    let rec retry = () => {
      subscribed := false;
      subRef := None;
      retries := retries^ + 1;

      let observer: Types.Observable.Observer.t('a) = {
        onSubscribe: (sub: Types.Subscription.t) => {
          if (finished^ || subscribed^) {
            sub.cancel();
          } else {
            subscribed := true;
            subRef := Some(sub);
          }
        },
        onComplete: () => {
          if (!finished^ && subscribed^) {
            obs.onComplete();
            subscription.cancel();
          }
        },
        onError: (x: exn) => {
          if (!finished^ && subscribed^) {
            switch(supplier(retries^)) {
              | true => {
                obs.onError(x);
                subscription.cancel();
              }
              | false => retry()
              | exception e => {
                obs.onError(e);
                subscription.cancel();
              }
            };
          } else {
            raise(x);
          }
        },
        onNext: (x: 'a) => {
          if (!finished^ && subscribed^) {
            obs.onNext(x);
          }
        },
      };
      source.subscribeWith(observer);
    };

    obs.onSubscribe(subscription);
    retry();
  }
};