// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var SafeSingleObserver$Reaxon = require("../../Observers/SafeSingleObserver.bs.js");

function operator(source) {
  return {
          subscribeWith: (function (obs) {
              var array = {
                contents: /* array */[]
              };
              var safe = SafeSingleObserver$Reaxon.make(obs);
              return Curry._1(source.subscribeWith, {
                          onSubscribe: (function (sub) {
                              return Curry._1(safe.onSubscribe, sub);
                            }),
                          onComplete: (function (param) {
                              return Curry._1(safe.onSuccess, array.contents);
                            }),
                          onError: (function (x) {
                              return Curry._1(safe.onError, x);
                            }),
                          onNext: (function (x) {
                              array.contents = $$Array.concat(/* :: */[
                                    array.contents,
                                    /* :: */[
                                      /* array */[x],
                                      /* [] */0
                                    ]
                                  ]);
                              return /* () */0;
                            })
                        });
            })
        };
}

exports.operator = operator;
/* No side effect */
