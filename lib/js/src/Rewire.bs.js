// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Rewire = require("rewire");

function MakeRewired() {
  return /* module */[
          /* __set__ */(function (prim, prim$1, prim$2) {
              return prim.__set__(prim$1, prim$2);
            }),
          /* __set__ */(function (prim, prim$1) {
              return prim.__set__(prim$1);
            }),
          /* __get__ */(function (prim, prim$1) {
              return prim.__get__(prim$1);
            }),
          /* __with__ */(function (prim, prim$1) {
              return prim.__with__(prim$1);
            }),
          /* __with__ */(function (prim, prim$1) {
              return prim.__with__(prim$1);
            })
        ];
}

function set(prim, prim$1, prim$2) {
  return prim.__set__(prim$1, prim$2);
}

function setAll(prim, prim$1) {
  return prim.__set__(prim$1);
}

function get(prim, prim$1) {
  return prim.__get__(prim$1);
}

function withRewiring(prim, prim$1) {
  return prim.__with__(prim$1);
}

function withAsyncRewiring(prim, prim$1) {
  return prim.__with__(prim$1);
}

var Rewired = /* module */[
  /* set */set,
  /* setAll */setAll,
  /* get */get,
  /* withRewiring */withRewiring,
  /* withAsyncRewiring */withAsyncRewiring
];

function MakeModuleRewiring() {
  return [(function (prim) {
              return Rewire(prim);
            })];
}

function rewire(prim) {
  return Rewire(prim);
}

exports.MakeRewired = MakeRewired;
exports.MakeModuleRewiring = MakeModuleRewiring;
exports.Rewired = Rewired;
exports.rewire = rewire;
/* rewire Not a pure module */