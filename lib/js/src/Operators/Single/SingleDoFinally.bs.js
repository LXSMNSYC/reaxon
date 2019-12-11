// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");

function operator(onFinally, source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeSingleObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, {
                                              cancel: (function (param) {
                                                  Curry._1(sub.cancel, /* () */0);
                                                  return Curry._1(onFinally, /* () */0);
                                                })
                                            });
                                }),
                              onSuccess: (function (x) {
                                  Curry._1(obs.onSuccess, x);
                                  return Curry._1(onFinally, /* () */0);
                                }),
                              onError: (function (x) {
                                  Curry._1(obs.onError, x);
                                  return Curry._1(onFinally, /* () */0);
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */