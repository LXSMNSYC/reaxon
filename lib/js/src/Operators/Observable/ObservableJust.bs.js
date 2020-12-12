// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var EmptySubscription$Reaxon = require("../../Utils/EmptySubscription.bs.js");
var SafeObservableObserver$Reaxon = require("../../Observers/SafeObservableObserver.bs.js");

function operator(value) {
  return {
          subscribeWith: (function (obs) {
              var safe = SafeObservableObserver$Reaxon.make(obs);
              Curry._1(safe.onSubscribe, EmptySubscription$Reaxon.instance);
              Curry._1(safe.onNext, value);
              return Curry._1(safe.onComplete, /* () */0);
            })
        };
}

exports.operator = operator;
/* No side effect */