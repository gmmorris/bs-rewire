// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';


function MakeRewired() {
  return /* module */[
          /* __set__ */(function (prim, prim$1, prim$2) {
              prim.__set__(prim$1, prim$2);
              return /* () */0;
            }),
          /* __set__ */(function (prim, prim$1) {
              prim.__set__(prim$1);
              return /* () */0;
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

function MakeModuleRewiring() {
  return /* module */[];
}

function set(prim, prim$1, prim$2) {
  prim.__set__(prim$1, prim$2);
  return /* () */0;
}

function setAll(prim, prim$1) {
  prim.__set__(prim$1);
  return /* () */0;
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

exports.MakeRewired = MakeRewired;
exports.MakeModuleRewiring = MakeModuleRewiring;
exports.Rewired = Rewired;
/* No side effect */
