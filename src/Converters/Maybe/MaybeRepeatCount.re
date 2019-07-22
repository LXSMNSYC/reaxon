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

let operator = (count: int, source: Types.Maybe.t('a)): Types.Observable.t('a) => {
  subscribeWith: (obs: Types.Observable.Observer.t('a)) => {
    let finished = ref(false);
    let subRef: ref(option(Types.Subscription.t)) = ref(None);

    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!finished^) {
          OptionalSubscription.cancel(subRef^);
          finished := true;
        }
      }
    };

    let retries = ref(-1);

    let rec retry = () => {
      subRef := None;

      if (retries^ < count) {
        retries := retries^ + 1;
        source.subscribeWith(ProtectedMaybeObserver.make({
          onSubscribe: (sub: Types.Subscription.t) => {
            if (finished^) {
              sub.cancel();
            } else {
              subRef := Some(sub);
            }
          },
          onComplete: () => {
            if (!finished^) {
              let oldRef = subRef^;

              retry();

              OptionalSubscription.cancel(oldRef);
            }
          },
          onSuccess: (x: 'a) => {
            if (!finished^) {
              let oldRef = subRef^;
  
              obs.onNext(x);
              retry();

              OptionalSubscription.cancel(oldRef);
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
        }));
      } else {
        obs.onComplete();
        subscription.cancel();
      }
    };

    obs.onSubscribe(subscription);
    retry();
  }
};