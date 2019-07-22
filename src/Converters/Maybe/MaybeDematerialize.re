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
let operator = (source: Types.Single.t(Types.Maybe.Notification.t('a))): Types.Maybe.t('a) => {
  subscribeWith: (obs: Types.Maybe.Observer.t('a)) => {
    source.subscribeWith(SafeSingleObserver.make({
      onSubscribe: (sub: Types.Subscription.t) => {
        obs.onSubscribe(sub);
      },
      onSuccess: (x: Types.Maybe.Notification.t('a)) => {
        switch (x) {
          | Types.Maybe.Notification.OnSuccess(item) => obs.onSuccess(item) 
          | Types.Maybe.Notification.OnError(item) => obs.onError(item)
          | Types.Maybe.Notification.OnComplete => obs.onComplete()
        };
      },
      onError: (x: exn) => {
        obs.onError(x);
      },
    }));
  },
};