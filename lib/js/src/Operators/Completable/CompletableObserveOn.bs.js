// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var OptionalSubscription$Reaxon = require("../../Utils/OptionalSubscription.bs.js");
var ProtectedCompletableObserver$Reaxon = require("../../Observers/ProtectedCompletableObserver.bs.js");

function operator(scheduler, source) {
  return {
          subscribeWith: (function (obs) {
              var alive = {
                contents: true
              };
              var outerRef = {
                contents: undefined
              };
              var innerRef = {
                contents: undefined
              };
              var subscription = {
                cancel: (function (param) {
                    if (alive.contents) {
                      OptionalSubscription$Reaxon.cancel(outerRef.contents);
                      OptionalSubscription$Reaxon.cancel(innerRef.contents);
                      alive.contents = false;
                      return /* () */0;
                    } else {
                      return 0;
                    }
                  })
              };
              return Curry._1(source.subscribeWith, ProtectedCompletableObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  if (alive.contents) {
                                    outerRef.contents = sub;
                                    return Curry._1(obs.onSubscribe, subscription);
                                  } else {
                                    return Curry._1(sub.cancel, /* () */0);
                                  }
                                }),
                              onComplete: (function (param) {
                                  if (alive.contents) {
                                    innerRef.contents = Curry._1(scheduler.run, (function (param) {
                                            Curry._1(obs.onComplete, /* () */0);
                                            return Curry._1(subscription.cancel, /* () */0);
                                          }));
                                    return OptionalSubscription$Reaxon.cancel(outerRef.contents);
                                  } else {
                                    return 0;
                                  }
                                }),
                              onError: (function (x) {
                                  if (alive.contents) {
                                    innerRef.contents = Curry._1(scheduler.run, (function (param) {
                                            Curry._1(obs.onError, x);
                                            return Curry._1(subscription.cancel, /* () */0);
                                          }));
                                    return OptionalSubscription$Reaxon.cancel(outerRef.contents);
                                  } else {
                                    throw x;
                                  }
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */