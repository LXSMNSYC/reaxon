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
let operator = (other: Types.Single.t('a), source: Types.Completable.t): Types.Single.t('a) => {
  subscribeWith: ({ onSubscribe, onSuccess, onError }: Types.Single.Observer.t('a)) => {
    let (alive, outer, inner, subscription) = DoubleSubscription.make();

    onSubscribe(subscription);

    let innerObserver = ProtectedSingleObserver.make({
      onSubscribe: (sub: Types.Subscription.t) => {
        if (alive^) {
          inner := Some(sub);
        } else {
          sub.cancel();
        }
      },
      onSuccess: (x: 'a) => {
        if (alive^) {
          onSuccess(x);
          subscription.cancel();
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
    });

    let outerObserver = ProtectedCompletableObserver.make({
      onSubscribe: (sub: Types.Subscription.t) => {
        if (alive^) {
          outer := Some(sub);
        } else {
          sub.cancel();
        }
      },
      onComplete: () => {
        if (alive^) {
          other.subscribeWith(innerObserver);
          OptionalSubscription.cancel(outer^);
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
    });

    source.subscribeWith(outerObserver);
  },
};