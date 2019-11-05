
let operator = (item, comparer, source) => {
  pub subscribeWith = (obs) => {
    let state = Cancellable.Linked.make();

    obs#onSubscribe(Utils.c2sub(state));

    source#subscribeWith({
      pub onSubscribe = state#link;
      pub onComplete = () => obs#onSuccess(false);

      pub onSuccess = (x) => switch (comparer(x, item)) {
        | result => obs#onSuccess(result)
        | exception e => obs#onError(e);
      };

      pub onError = obs#onError;
    })
  };
};

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
let operator = (item: 'a, comparer: 'a => 'a => bool, source: Types.Maybe.t('a)): Types.Single.t(bool) => {
  subscribeWith: (obs: Types.Single.Observer.t(bool)) => {
    let safe = SafeSingleObserver.make(obs);

    source.subscribeWith({
      onSubscribe: (subscription: Types.Subscription.t) => {
        safe.onSubscribe(subscription);
      },
      onComplete: () => {
        safe.onSuccess(false);
      },
      onSuccess: (x: 'a) => {
        switch (comparer(x, item)) {
          | result => safe.onSuccess(result);
          | exception e => safe.onError(e);
        }
      },
      onError: (err: exn) => {
        safe.onError(err);
      },
    });
  },
}