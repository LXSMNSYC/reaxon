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
let operator = (scheduler: Types.Scheduler.t, source: Types.Single.t('a)): Types.Single.t('a) => {
  subscribeWith: (obs: Types.Single.Observer.t('a)) => {
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

    let observer: Types.Single.Observer.t('a) = ProtectedSingleObserver.make({
      onSubscribe: (sub: Types.Subscription.t) => {
        if (alive^) {
          outerRef := Some(sub);
          obs.onSubscribe(subscription);
        } else {
          sub.cancel();
        }
      },
      onSuccess: (x: 'a) => {
        if (alive^) {
          innerRef := Some(scheduler.run(() => {
            obs.onSuccess(x);
            subscription.cancel();
          }));
          OptionalSubscription.cancel(outerRef^);
        }
      },
      onError: (x: exn) => {
        if (alive^) {
          innerRef := Some(scheduler.run(() => {
            obs.onError(x);
            subscription.cancel();
          }));
          OptionalSubscription.cancel(outerRef^);
        } else {
          raise(x);
        }
      },
    });

    source.subscribeWith(observer);
  }
}