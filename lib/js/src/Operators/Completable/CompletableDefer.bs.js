// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var CompletableError$Reaxon = require("./CompletableError.bs.js");
var SafeCompletableObserver$Reaxon = require("../../Observers/SafeCompletableObserver.bs.js");

function operator(supplier) {
  return {
          subscribeWith: (function (obs) {
              var result;
              try {
                result = Curry._1(supplier, /* () */0);
              }
              catch (raw_e){
                var e = Caml_js_exceptions.internalToOCamlException(raw_e);
                return Curry._1(CompletableError$Reaxon.operator(e).subscribeWith, obs);
              }
              return Curry._1(result.subscribeWith, SafeCompletableObserver$Reaxon.make(obs));
            })
        };
}

exports.operator = operator;
/* No side effect */