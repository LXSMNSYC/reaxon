// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");

function operator(onTerminate, source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeSingleObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, sub);
                                }),
                              onSuccess: (function (x) {
                                  Curry._1(onTerminate, /* () */0);
                                  return Curry._1(obs.onSuccess, x);
                                }),
                              onError: (function (x) {
                                  Curry._1(onTerminate, /* () */0);
                                  return Curry._1(obs.onError, x);
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */
