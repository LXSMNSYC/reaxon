// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeMaybeObserver$Reaxon = require("../../Observers/SafeMaybeObserver.bs.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");
var CompositeSubscription$Reaxon = require("../../Utils/CompositeSubscription.bs.js");

function operator(other, source) {
  return {
          subscribeWith: (function (obs) {
              var composite = CompositeSubscription$Reaxon.make(/* () */0);
              var alive = composite.alive;
              var subscription = composite.subscription;
              var aFinished = {
                contents: false
              };
              var bFinished = {
                contents: false
              };
              Curry._1(obs.onSubscribe, subscription);
              Curry._1(source.subscribeWith, SafeMaybeObserver$Reaxon.make({
                        onSubscribe: (function (sub) {
                            return Curry._1(composite.add, sub);
                          }),
                        onComplete: (function (param) {
                            if (Curry._1(alive, /* () */0)) {
                              aFinished.contents = true;
                              if (bFinished.contents) {
                                Curry._1(obs.onComplete, /* () */0);
                                return Curry._1(subscription.cancel, /* () */0);
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }),
                        onSuccess: (function (x) {
                            if (Curry._1(alive, /* () */0)) {
                              aFinished.contents = true;
                              Curry._1(obs.onNext, x);
                              if (bFinished.contents) {
                                Curry._1(obs.onComplete, /* () */0);
                                return Curry._1(subscription.cancel, /* () */0);
                              } else {
                                return 0;
                              }
                            } else {
                              return 0;
                            }
                          }),
                        onError: (function (x) {
                            if (Curry._1(alive, /* () */0)) {
                              Curry._1(obs.onError, x);
                              return Curry._1(subscription.cancel, /* () */0);
                            } else {
                              throw x;
                            }
                          })
                      }));
              return Curry._1(other.subscribeWith, SafeSingleObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(composite.add, sub);
                                }),
                              onSuccess: (function (x) {
                                  if (Curry._1(alive, /* () */0)) {
                                    bFinished.contents = true;
                                    Curry._1(obs.onNext, x);
                                    if (aFinished.contents) {
                                      Curry._1(obs.onComplete, /* () */0);
                                      return Curry._1(subscription.cancel, /* () */0);
                                    } else {
                                      return 0;
                                    }
                                  } else {
                                    return 0;
                                  }
                                }),
                              onError: (function (x) {
                                  if (Curry._1(alive, /* () */0)) {
                                    Curry._1(obs.onError, x);
                                    return Curry._1(subscription.cancel, /* () */0);
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
