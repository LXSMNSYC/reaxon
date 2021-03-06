// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var OptionalSubscription$Reaxon = require("../../Utils/OptionalSubscription.bs.js");
var ProtectedMaybeObserver$Reaxon = require("../../Observers/ProtectedMaybeObserver.bs.js");

function operator(count, source) {
  return {
          subscribeWith: (function (obs) {
              var alive = {
                contents: true
              };
              var subRef = {
                contents: undefined
              };
              var subscription = {
                cancel: (function (param) {
                    if (alive.contents) {
                      OptionalSubscription$Reaxon.cancel(subRef.contents);
                      alive.contents = false;
                      return /* () */0;
                    } else {
                      return 0;
                    }
                  })
              };
              var retries = {
                contents: -1
              };
              var retry = function (param) {
                subRef.contents = undefined;
                if (retries.contents < count) {
                  retries.contents = retries.contents + 1 | 0;
                  return Curry._1(source.subscribeWith, ProtectedMaybeObserver$Reaxon.make({
                                  onSubscribe: (function (sub) {
                                      if (alive.contents) {
                                        subRef.contents = sub;
                                        return /* () */0;
                                      } else {
                                        return Curry._1(sub.cancel, /* () */0);
                                      }
                                    }),
                                  onComplete: (function (param) {
                                      if (alive.contents) {
                                        var oldRef = subRef.contents;
                                        retry(/* () */0);
                                        return OptionalSubscription$Reaxon.cancel(oldRef);
                                      } else {
                                        return 0;
                                      }
                                    }),
                                  onSuccess: (function (x) {
                                      if (alive.contents) {
                                        var oldRef = subRef.contents;
                                        Curry._1(obs.onNext, x);
                                        retry(/* () */0);
                                        return OptionalSubscription$Reaxon.cancel(oldRef);
                                      } else {
                                        return 0;
                                      }
                                    }),
                                  onError: (function (x) {
                                      if (alive.contents) {
                                        Curry._1(obs.onError, x);
                                        return Curry._1(subscription.cancel, /* () */0);
                                      } else {
                                        throw x;
                                      }
                                    })
                                }));
                } else {
                  Curry._1(obs.onComplete, /* () */0);
                  return Curry._1(subscription.cancel, /* () */0);
                }
              };
              Curry._1(obs.onSubscribe, subscription);
              return retry(/* () */0);
            })
        };
}

exports.operator = operator;
/* No side effect */
