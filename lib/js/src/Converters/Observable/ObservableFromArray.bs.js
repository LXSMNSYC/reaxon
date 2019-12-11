// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var EmptySubscription$Reaxon = require("../../Utils/EmptySubscription.bs.js");
var SafeObservableObserver$Reaxon = require("../../Observers/SafeObservableObserver.bs.js");

function operator(source) {
  return {
          subscribeWith: (function (obs) {
              var safe = SafeObservableObserver$Reaxon.make(obs);
              Curry._1(safe.onSubscribe, EmptySubscription$Reaxon.instance);
              $$Array.iter((function (x) {
                      return Curry._1(safe.onNext, x);
                    }), source);
              return Curry._1(safe.onComplete, /* () */0);
            })
        };
}

exports.operator = operator;
/* No side effect */