// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var SafeMaybeObserver$Reaxon = require("../../Observers/SafeMaybeObserver.bs.js");

function operator(source) {
  return {
          subscribeWith: (function (obs) {
              return Curry._1(source.subscribeWith, SafeMaybeObserver$Reaxon.make(obs));
            })
        };
}

exports.operator = operator;
/* No side effect */
