open Jest;

open Rewire;

let testAssetLocation = "../../../__tests__/assets/testAsset.js";
module TestAssetModule = {
  include
    MakeRewired(
      {
        type t;
      },
    );
  [@bs.send] external getParam : t => string = "";
};

module TestAssetRewirting = {
  include MakeModuleRewiring(TestAssetModule);
};

describe("Rewire", () =>
  Expect.(
    test(
      "MakeRewired & MakeModuleRewiring can be used to define custom module APIs",
      () => {
      let rewiredModule = TestAssetRewirting.rewire(testAssetLocation);
      expect(TestAssetModule.getParam(rewiredModule))
      |> toEqual("someValue");
    })
  )
);