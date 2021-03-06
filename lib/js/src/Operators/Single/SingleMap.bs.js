// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");

function operator(mapper, source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeSingleObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, sub);
                                }),
                              onSuccess: (function (x) {
                                  var result;
                                  try {
                                    result = Curry._1(mapper, x);
                                  }
                                  catch (raw_err){
                                    return Curry._1(obs.onError, Caml_js_exceptions.internalToOCamlException(raw_err));
                                  }
                                  return Curry._1(obs.onSuccess, result);
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
