open Jest;

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
      let rewiredModule = Rewire.rewire("./testAsset.js");
      expect(getParam(rewiredModule)) |> toEqual("someValue");
    })
  );
  Expect.(
    test("rewire.get gets a named value in a module", () => {
      let rewiredModule = Rewire.rewire("./testAsset.js");
      expect(Rewire.get(rewiredModule, "someModule"))
      |> toEqual(oneParamModuleToJs({param: "someValue"}));
    })
  );
  Expect.(
    test("rewire.set sets a value in a module", () => {
      let rewiredModule = Rewire.rewire("./testAsset.js");
      expect(getParam(rewiredModule)) |> toEqual("someValue");
      Rewire.set(
        rewiredModule,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      expect(getParam(rewiredModule)) |> toEqual("someMockedValue");
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
      let rewiredModule = Rewire.rewire("./testAsset.js");
      Rewire.setAll(rewiredModule, all);
      expect(getParam(rewiredModule)) |> toEqual("someMockedValue");
      expect(getOtherParam(rewiredModule))
      |> toEqual("someOtherMockedValue");
    })
  );
  Expect.(
    testAsync("rewire.withRewiring takes a callback in which values are mocked", finish => {
      let rewiredModule = Rewire.rewire("./testAsset.js");
      let all = Js.Dict.empty();
      Js.Dict.set(
        all,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      let rewiringCallback = Rewire.withRewiring(rewiredModule, all);
      rewiringCallback(() =>
        finish(
          expect(getParam(rewiredModule)) |> toEqual("someMockedValue"),
        )
      );
    })
  );
  Expect.(
    testAsync("rewire.withAsyncRewiring take a promised callback which resolves with variables reset to their original value", finish => {
      let rewiredModule = Rewire.rewire("./testAsset.js");
      let all = Js.Dict.empty();
      Js.Dict.set(
        all,
        "someModule",
        oneParamModuleToJs({param: "someMockedValue"}),
      );
      let rewiringCallback = Rewire.withAsyncRewiring(rewiredModule, all);
      rewiringCallback(() => Js.Promise.resolve())
      |> Js.Promise.then_(_ => Js.Promise.resolve(finish(expect(getParam(rewiredModule)) |> toEqual("someValue"))))
      |> ignore;
      ();
    })
  );
});