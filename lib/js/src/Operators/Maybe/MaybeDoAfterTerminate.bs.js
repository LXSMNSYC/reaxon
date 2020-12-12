// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeMaybeObserver$Reaxon = require("../../Observers/SafeMaybeObserver.bs.js");

function operator(onTerminate, source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeMaybeObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, sub);
                                }),
                              onComplete: (function (param) {
                                  Curry._1(obs.onComplete, /* () */0);
                                  return Curry._1(onTerminate, /* () */0);
                                }),
                              onSuccess: (function (x) {
                                  Curry._1(obs.onSuccess, x);
                                  return Curry._1(onTerminate, /* () */0);
                                }),
                              onError: (function (x) {
                                  Curry._1(obs.onError, x);
                                  return Curry._1(onTerminate, /* () */0);
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */