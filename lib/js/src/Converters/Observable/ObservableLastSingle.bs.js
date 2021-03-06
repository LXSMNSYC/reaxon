// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var SafeObservableObserver$Reaxon = require("../../Observers/SafeObservableObserver.bs.js");

function operator(defaultItem, source) {
  return {
          subscribeWith: (function (obs) {
              var last = {
                contents: undefined
              };
              return Curry._1(source.subscribeWith, SafeObservableObserver$Reaxon.make({
                              onSubscribe: (function (sub) {
                                  return Curry._1(obs.onSubscribe, sub);
                                }),
                              onComplete: (function (param) {
                                  var match = last.contents;
                                  if (match !== undefined) {
                                    return Curry._1(obs.onSuccess, Caml_option.valFromOption(match));
                                  } else {
                                    return Curry._1(obs.onSuccess, defaultItem);
                                  }
                                }),
                              onError: (function (x) {
                                  return Curry._1(obs.onError, x);
                                }),
                              onNext: (function (x) {
                                  last.contents = Caml_option.some(x);
                                  return /* () */0;
                                })
                            }));
            })
        };
}

exports.operator = operator;
/* No side effect */
