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
let operator = (sources: list(Types.Maybe.t('a))): Types.Observable.t('a) => {
  subscribeWith: ({ onSubscribe, onComplete, onError, onNext }: Types.Observable.Observer.t('a)) => {
    let alive = ref(true);

    let subRef = ref(None);

    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (alive^) {
          OptionalSubscription.cancel(subRef^);
          alive := false;
        }
      }
    };

    let max = List.length(sources);

    let rec subscribe = (index) => {
      if (index >= max) {
        onComplete();
        subscription.cancel();
      } else {
        subRef := None;
        (sources->List.nth(index)).subscribeWith(ProtectedMaybeObserver.make({
          onSubscribe: (sub: Types.Subscription.t) => {
            if (alive^) {
              subRef := Some(sub);
            } else {
              sub.cancel();
            }
          },
          onComplete: () => {
            if (alive^) {
              let oldRef = subRef^;
              subscribe(index + 1);
              OptionalSubscription.cancel(oldRef);
            }
          },
          onSuccess: (x: 'a) => {
            if (alive^) {
              let oldRef = subRef^;
              onNext(x);
              subscribe(index + 1);
              OptionalSubscription.cancel(oldRef);
            }
          },
          onError: (x: exn) => {
            if (alive^) {
              onError(x);
              subscription.cancel();
            } else {
              raise(x);
            }
          },
        }));
      }
    };

    onSubscribe(subscription);
    subscribe(0);
  }
};