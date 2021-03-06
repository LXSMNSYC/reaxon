// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var SafeMaybeObserver$Reaxon = require("../../Observers/SafeMaybeObserver.bs.js");

function operator(item, comparer, source) {
  return {
          subscribeWith: (function (param) {
              var onError = param.onError;
              var onSuccess = param.onSuccess;
              return Curry._1(source.subscribeWith, SafeMaybeObserver$Reaxon.make({
                              onSubscribe: param.onSubscribe,
                              onComplete: (function (param) {
                                  return Curry._1(onSuccess, false);
                                }),
                              onSuccess: (function (x) {
                                  var result;
                                  try {
                                    result = Curry._2(comparer, x, item);
                                  }
                                  catch (raw_e){
                                    return Curry._1(onError, Caml_js_exceptions.internalToOCamlException(raw_e));
                                  }
                                  return Curry._1(onSuccess, result);
                                }),
                              onError: onError
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */
