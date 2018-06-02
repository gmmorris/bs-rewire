// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/src/jest.js");
var Rewire = require("rewire");
var Rewire$BsRewire = require("../src/Rewire.bs.js");

var include = Rewire$BsRewire.MakeRewired(/* module */[]);

var TestAssetModule_000 = /* set */include[0];

var TestAssetModule_001 = /* setAll */include[1];

var TestAssetModule_002 = /* get */include[2];

var TestAssetModule_003 = /* withRewiring */include[3];

var TestAssetModule_004 = /* withAsyncRewiring */include[4];

var TestAssetModule = /* module */[
  TestAssetModule_000,
  TestAssetModule_001,
  TestAssetModule_002,
  TestAssetModule_003,
  TestAssetModule_004
];

Rewire$BsRewire.MakeModuleRewiring([]);

var TestAssetRewirting = /* module */[];

describe("Rewire", (function () {
        return Jest.test("MakeRewired & MakeModuleRewiring can be used to define custom module APIs", (function () {
                      var rewiredModule = Rewire("./assets/testAsset.js");
                      return Jest.Expect[/* toEqual */12]("someValue", Jest.Expect[/* expect */0](rewiredModule.getParam()));
                    }));
      }));

exports.TestAssetModule = TestAssetModule;
exports.TestAssetRewirting = TestAssetRewirting;
/* include Not a pure module */