// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");

function operator(source) {
  return {
          subscribeWith: (function (param) {
              var onError = param.onError;
              var onSuccess = param.onSuccess;
              var onComplete = param.onComplete;
              return Curry._1(source.subscribeWith, SafeSingleObserver$Reaxon.make({
                              onSubscribe: param.onSubscribe,
                              onSuccess: (function (x) {
                                  if (typeof x === "number") {
                                    return Curry._1(onComplete, /* () */0);
                                  } else if (x.tag) {
                                    return Curry._1(onError, x[0]);
                                  } else {
                                    return Curry._1(onSuccess, x[0]);
                                  }
                                }),
                              onError: onError
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */