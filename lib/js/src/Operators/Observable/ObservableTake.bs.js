// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeObservableObserver$Reaxon = require("../../Observers/SafeObservableObserver.bs.js");

function operator(count, source) {
  return {
          subscribeWith: (function (obs) {
              var size = {
                contents: count
              };
              return Curry._1(source.subscribeWith, SafeObservableObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, sub);
                                }),
                              onComplete: (function (param) {
                                  return Curry._1(obs.onComplete, /* () */0);
                                }),
                              onError: (function (x) {
                                  return Curry._1(obs.onError, x);
                                }),
                              onNext: (function (x) {
                                  if (size.contents > 0) {
                                    size.contents = size.contents - 1 | 0;
                                    return Curry._1(obs.onNext, x);
                                  } else {
                                    return 0;
                                  }
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */