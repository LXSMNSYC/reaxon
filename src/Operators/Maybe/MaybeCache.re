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
let operator = (source: Types.Maybe.t('a)): Types.Maybe.t('a) => {
  let cached = ref(false);
  let subscribed = ref(false);
  let observers: ref(list(Types.Maybe.Observer.t('a))) = ref([]);
  let signal: ref(option(Types.Maybe.Notification.t('a))) = ref(None);

  {
    subscribeWith: (obs: Types.Maybe.Observer.t('a)) => {
      if (cached^) {
        let safe = SafeMaybeObserver.make(obs);

        safe.onSubscribe(EmptySubscription.instance);
        
        switch (signal^) {
          | Some(item) => {
            switch (item) {
              | Types.Maybe.Notification.OnSuccess(x) => safe.onSuccess(x)
              | Types.Maybe.Notification.OnComplete => safe.onComplete()
              | Types.Maybe.Notification.OnError(e) => safe.onError(e)
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

          source.subscribeWith(SafeMaybeObserver.make({
            onSubscribe: (sub: Types.Subscription.t) => {
              subRef := Some(sub);
            },
            onComplete: () => {
              if (!cached^) {
                cached := true;

                signal := Some(Types.Maybe.Notification.OnComplete);

                observers^ |> List.iter((observer: Types.Maybe.Observer.t('a)) => {
                  observer.onComplete();
                });

                OptionalSubscription.cancel(subRef^);
              }
            },
            onSuccess: (x: 'a) => {
              if (!cached^) {
                cached := true;

                signal := Some(Types.Maybe.Notification.OnSuccess(x));

                observers^ |> List.iter((observer: Types.Maybe.Observer.t('a)) => {
                  observer.onSuccess(x);
                });

                OptionalSubscription.cancel(subRef^);
              }
            },
            onError: (x: exn) => {
              if (!cached^) {
                cached := true;

                signal := Some(Types.Maybe.Notification.OnError(x));

                observers^ |> List.iter((observer: Types.Maybe.Observer.t('a)) => {
                  observer.onError(x);
                });

                OptionalSubscription.cancel(subRef^);
              }
            },
          }));
        }
      }
    },
  }
};