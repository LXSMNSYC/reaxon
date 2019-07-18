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
let operator = (other: Types.Completable.t, source: Types.Completable.t): Types.Completable.t => {
  subscribeWith: (obs: Types.Completable.Observer.t) => {
    let aFinished = ref(false);
    let bFinished = ref(false);
    let aRef: ref(option(Types.Subscription.t)) = ref(None);
    let bRef: ref(option(Types.Subscription.t)) = ref(None);
    let aSub = ref(false);
    let bSub = ref(false);

    let aCancel = () => {
      if (aSub^) {
        switch (aRef^) {
        | Some(ref) => ref.cancel()
        | None => ()
        }
      }
      aFinished := true;
    };

    let bCancel = () => {
      if (bSub^) {
        switch (bRef^) {
        | Some(ref) => ref.cancel()
        | None => ()
        }
      }
      bFinished := true;
    };
    
    let subscription: Types.Subscription.t = {
      cancel: () => {
        if (!(aFinished^ && bFinished^)) {
          aCancel();
          bCancel();
        }
      }
    };

    obs.onSubscribe(subscription);
    source.subscribeWith({
      onSubscribe: (sub: Types.Subscription.t) => {
        if (aFinished^ || aSub^) {
          sub.cancel();
        } else {
          aSub := true;
          aRef := Some(sub);
        }
      },
      onComplete: () => {
        if (!aFinished^ && aSub^) {
          if (bFinished^) {
            obs.onComplete();
            subscription.cancel();
          }
          aCancel();
        }
      },
      onError: (x: exn) => {
        if (!aFinished^ && aSub^) {
          obs.onError(x);
          subscription.cancel();
        } else {
          raise(x);
        }
      },
    });
    other.subscribeWith({
      onSubscribe: (sub: Types.Subscription.t) => {
        if (bFinished^ || bSub^) {
          sub.cancel();
        } else {
          bSub := true;
          bRef := Some(sub);
        }
      },
      onComplete: () => {
        if (!bFinished^ && bSub^) {
          if (aFinished^) {
            obs.onComplete();
            subscription.cancel();
          }
          bCancel();
        }
      },
      onError: (x: exn) => {
        if (!bFinished^ && bSub^) {
          obs.onError(x);
          subscription.cancel();
        } else {
          raise(x);
        }
      },
    });
  }
};