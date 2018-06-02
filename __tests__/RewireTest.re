open Jest;
open Rewire;
let getParam = [%raw
  {|
        function(rewiredModule) {
          return rewiredModule.getParam();
        }
      |}
];

let getOtherParam = [%raw
  {|
      function(rewiredModule) {
        return rewiredModule.getOtherParam();
      }
    |}
];

[@bs.deriving jsConverter]
type oneParamModule = {param: string};

describe("Rewire", () => {
  Expect.(
    test("rewire requires a module", () => {
      let rewiredModule = rewire("./assets/testAsset.js");
      expect(getParam(rewiredModule)) |> toEqual("someValue");
    })
  );   
  Expect.(
    test("rewire.get gets a named value in a module", () => {
      let rewiredModule = rewire("./assets/testAsset.js");
      expect(Rewired.get(rewiredModule, "someModule"))
      |> toEqual(oneParamModuleToJs({param: "someValue"}));
    })
  );
  Expect.(
    test("rewire.set sets a value in a module", () => {
      let rewiredModule = rewire("./assets/testAsset.js");
      expect(getParam(rewiredModule)) |> toEqual("someValue");
      Rewired.set(
        rewiredModule,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      expect(getParam(rewiredModule)) |> toEqual("someMockedValue");
    })
  );
  Expect.(
    test("rewire.set returns a reset function", () => {
      let rewiredModule = rewire("./assets/testAsset.js");
      expect(getParam(rewiredModule)) |> toEqual("someValue");
      let reset = Rewired.set(
        rewiredModule,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      expect(getParam(rewiredModule)) |> toEqual("someMockedValue");
      reset();
      expect(getParam(rewiredModule)) |> toEqual("someValue");
    })
  );
  Expect.(
    test("rewire.setAll sets multiple values in a module", () => {
      let all = Js.Dict.empty();
      Js.Dict.set(
        all,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      Js.Dict.set(
        all,
        "someOtherModule",
        oneParamModuleToJs({param: "someOtherMockedValue"}),
      );
      let rewiredModule = rewire("./assets/testAsset.js");
      Rewired.setAll(rewiredModule, all);
      expect(getParam(rewiredModule)) |> toEqual("someMockedValue");
      expect(getOtherParam(rewiredModule))
      |> toEqual("someOtherMockedValue");
    })
  );
  Expect.(
    testAsync("rewire.withRewiring takes a callback in which values are mocked", finish => {
      let rewiredModule = rewire("./assets/testAsset.js");
      let all = Js.Dict.empty();
      Js.Dict.set(
        all,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      let rewiringCallback = Rewired.withRewiring(rewiredModule, all);
      rewiringCallback(() =>
        finish(
          expect(getParam(rewiredModule)) |> toEqual("someMockedValue"),
        )
      );
    })
  );
  Expect.(
    testAsync("rewire.withAsyncRewiring take a promised callback which resolves with variables reset to their original value", finish => {
      let rewiredModule = rewire("./assets/testAsset.js");
      let all = Js.Dict.empty();
      Js.Dict.set(
        all,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      let rewiringCallback = Rewired.withAsyncRewiring(rewiredModule, all);
      rewiringCallback(() => Js.Promise.resolve())
      |> Js.Promise.then_(_ => Js.Promise.resolve(finish(expect(getParam(rewiredModule)) |> toEqual("someValue"))))
      |> ignore;
      ();
    })
  );
});