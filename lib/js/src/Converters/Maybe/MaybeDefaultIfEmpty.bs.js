// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeMaybeObserver$Reaxon = require("../../Observers/SafeMaybeObserver.bs.js");

function operator(item, source) {
  return {
          subscribeWith: (function (param) {
              var onSuccess = param.onSuccess;
              return Curry._1(source.subscribeWith, SafeMaybeObserver$Reaxon.make({
                              onSubscribe: param.onSubscribe,
                              onComplete: (function (param) {
                                  return Curry._1(onSuccess, item);
                                }),
                              onSuccess: Curry.__1(onSuccess),
                              onError: param.onError
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */
