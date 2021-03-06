// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeCompletableObserver$Reaxon = require("../../Observers/SafeCompletableObserver.bs.js");

function operator(onCancel, source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeCompletableObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, {
                                              cancel: (function (param) {
                                                  Curry._1(sub.cancel, /* () */0);
                                                  return Curry._1(onCancel, /* () */0);
                                                })
                                            });
                                }),
                              onComplete: (function (param) {
                                  return Curry._1(obs.onComplete, /* () */0);
                                }),
                              onError: (function (x) {
                                  return Curry._1(obs.onError, x);
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */
