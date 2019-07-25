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
let operator = (source: Types.Completable.t): Types.Completable.t => {
  let cached = ref(false);
  let subscribed = ref(false);
  let observers: ref(list(Types.Completable.Observer.t)) = ref([]);
  let signal: ref(option(Types.Completable.Notification.t)) = ref(None);

  {
    subscribeWith: (obs: Types.Completable.Observer.t) => {
      if (cached^) {
        let safe = SafeCompletableObserver.make(obs);

        safe.onSubscribe(EmptySubscription.instance);
        
        switch (signal^) {
          | Some(item) => {
            switch (item) {
              | Types.Completable.Notification.OnComplete => safe.onComplete()
              | Types.Completable.Notification.OnError(e) => safe.onError(e)
            }
          }
          | None => ()
        }
      } else {
        let alive = ref(true);

        observers := [obs] @ observers^;

        let subscription: Types.Subscription.t = {
          cancel: () => {
            if (alive^) {
              observers := observers^ |> List.filter(x => x == obs);
              alive := false;
            }
          }
        };

        obs.onSubscribe(subscription);

        if (!subscribed^) {
          subscribed := true;
          
          let subRef = ref(None);

          source.subscribeWith(SafeCompletableObserver.make({
            onSubscribe: (sub: Types.Subscription.t) => {
              subRef := Some(sub);
            },
            onComplete: () => {
              if (!cached^) {
                cached := true;

                signal := Some(Types.Completable.Notification.OnComplete);

                observers^ |> List.iter((observer: Types.Completable.Observer.t) => {
                  observer.onComplete();
                });

                OptionalSubscription.cancel(subRef^);
              }
            },
            onError: (x: exn) => {
              if (!cached^) {
                cached := true;

                signal := Some(Types.Completable.Notification.OnError(x));

                observers^ |> List.iter((observer: Types.Completable.Observer.t) => {
                  observer.onError(x);
                });

                OptionalSubscription.cancel(subRef^);
              }
            },
          }))
        }
      }
    },
  }
};