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
let operator = (mapper: 'a => 'b, source: Types.Observable.t('a)): Types.Observable.t('b) => {
  subscribeWith: (obs: Types.Observable.Observer.t('b)) => {
    let safe: Types.Observable.Observer.t('b) = SafeObservableObserver.make(obs);

    let observer: Types.Observable.Observer.t('a) = {
      onSubscribe: (sub: Types.Subscription.t) => {
        safe.onSubscribe(sub);
      },
      onNext: (x: 'a) => {
        switch (mapper(x)) {
          | result => obs.onNext(result)
          | exception err => obs.onError(err)
        }
      },
      onComplete: () => {
        safe.onComplete();
      },
      onError: (x: exn) => {
        safe.onError(x);
      },
    };

    source.subscribeWith(observer);
  }
};
