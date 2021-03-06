// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");

function make(param) {
  var alive = {
    contents: true
  };
  var container = {
    contents: /* [] */0
  };
  return {
          subscription: {
            cancel: (function (param) {
                if (alive.contents) {
                  return List.iter((function (sub) {
                                return Curry._1(sub.cancel, /* () */0);
                              }), container.contents);
                } else {
                  return 0;
                }
              })
          },
          container: container,
          alive: (function (param) {
              return alive.contents;
            }),
          add: (function (sub) {
              if (alive.contents) {
                container.contents = Pervasives.$at(/* :: */[
                      sub,
                      /* [] */0
                    ], container.contents);
                return /* () */0;
              } else {
                return Curry._1(sub.cancel, /* () */0);
              }
            }),
          remove: (function (sub) {
              if (alive.contents) {
                container.contents = List.filter((function (x) {
                          return Caml_obj.caml_notequal(x, sub);
                        }))(container.contents);
                return /* () */0;
              } else {
                return 0;
              }
            })
        };
}

exports.make = make;
/* No side effect */
