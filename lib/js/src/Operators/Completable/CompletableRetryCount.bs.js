// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var OptionalSubscription$Reaxon = require("../../Utils/OptionalSubscription.bs.js");
var ProtectedCompletableObserver$Reaxon = require("../../Observers/ProtectedCompletableObserver.bs.js");

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
                retries.contents = retries.contents + 1 | 0;
                return Curry._1(source.subscribeWith, ProtectedCompletableObserver$Reaxon.make({
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
                                      Curry._1(obs.onComplete, /* () */0);
                                      return Curry._1(subscription.cancel, /* () */0);
                                    } else {
                                      return 0;
                                    }
                                  }),
                                onError: (function (x) {
                                    if (alive.contents) {
                                      if (retries.contents < count) {
                                        var oldRef = subRef.contents;
                                        retry(/* () */0);
                                        return OptionalSubscription$Reaxon.cancel(oldRef);
                                      } else {
                                        Curry._1(obs.onError, x);
                                        return Curry._1(subscription.cancel, /* () */0);
                                      }
                                    } else {
                                      throw x;
                                    }
                                  })
                              }));
              };
              Curry._1(obs.onSubscribe, subscription);
              return retry(/* () */0);
            })
        };
}

exports.operator = operator;
/* No side effect */