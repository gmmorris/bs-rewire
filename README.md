# bs-rewire ![alt TravisCI Build](https://travis-ci.org/gmmorris/bs-rewire.svg?branch=master)

[BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [Rewire](https://github.com/jhnns/rewire)


## Example

```reason
open Jest;

describe("Expect", () => {
  open Expect;

  let getParam = [%raw
    {|
          function(rewiredModule) {
            return rewiredModule.getParam();
          }
        |}
  ];

  test("rewire.set sets a value in a module", () => {
    let rewiredModule = Rewire.rewire("./testAsset.js");

    Rewire.set(
      rewiredModule,
      "someModule",
      oneParamModuleToJs({param: "someMockedValue"}),
    );

    expect(
      getParam(rewiredModule)
    ) |> toEqual("someMockedValue");
  })
});


```

See [the tests](https://github.com/gmmorris/bs-rewire/tree/master/__tests__) for more examples.

## Installation

```sh
npm install --save-dev @gmmorris/bs-rewire
```

Then add `@gmmorris/bs-rewire` to `bs-dev-dependencies` in your `bsconfig.json`:
```js
{
  ...
  "bs-dev-dependencies": ["@gmmorris/bs-rewire"]
}
```
