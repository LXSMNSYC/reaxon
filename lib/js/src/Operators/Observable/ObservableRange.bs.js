// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var EmptySubscription$Reaxon = require("../../Utils/EmptySubscription.bs.js");
var SafeObservableObserver$Reaxon = require("../../Observers/SafeObservableObserver.bs.js");

function operator(low, high, step) {
  return {
          subscribeWith: (function (obs) {
              var safe = SafeObservableObserver$Reaxon.make(obs);
              Curry._1(safe.onSubscribe, EmptySubscription$Reaxon.instance);
              var generate = function (_current) {
                while(true) {
                  var current = _current;
                  if (step < 0 && current >= high || step > 0 && current <= high) {
                    Curry._1(safe.onNext, current);
                    _current = current + step | 0;
                    continue ;
                  } else {
                    return 0;
                  }
                };
              };
              generate(low);
              return Curry._1(safe.onComplete, /* () */0);
            })
        };
}

exports.operator = operator;
/* No side effect */