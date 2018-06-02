# bs-rewire ![alt TravisCI Build](https://travis-ci.org/gmmorris/bs-rewire.svg?branch=master)

[BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [Rewire](https://github.com/jhnns/rewire)

Rewire adds a special setter and getter to modules so you can modify their behaviour for better unit testing.
bs-rewire provides the bindings to allow you to use the familiar rewire approach to test your ReasonML and oCaml code when targetting the Node ecosystem through Bucklescript (damn, that was amouthful, wasn't it?).

<br />

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
<br />

API
---

### rewire(filename: String): Rewire.RewiredModule

Returns a rewired version of the module found at `filename`.
Use `Rewire.rewire()` exactly like the JS version `rewire()`.

### Rewired.set(Rewire.RewiredModule, name : string, value: 'a) : (Rewired.reset: unit => unit)

Sets the internal variable `name` to the given `value`. Returns a function which can be called to revert the change.

### Rewired.setAll(Rewire.RewiredModule, values : Js.Dict.t('a)) : (Rewired.reset: unit => unit)

Takes all keys of `dict` as variable names and sets the values respectively. Returns a function which can be called to revert the change.

### Rewired.get(Rewire.RewiredModule, name : string) : 'a

Returns the private variable with the given `name`.

### Rewired.withRewiring(Rewire.RewiredModule, values : Js.Dict.t('a)) : (Rewired.rewiringExecutor : unit => unit => unit)

Returns a function which - when being called - sets `obj`, executes the given `callback` and reverts `obj`.

### Rewired.withAsyncRewiring(Rewire.RewiredModule, values : Js.Dict.t('a)) : (Rewired.rewiringAsyncExecutor : unit => Js.Promise.t('x))

Returns a function which - when being called - sets `obj`, executes the given `callback` and expects a Promise to be returned.
`obj` is only reverted after the promise has been resolved or rejected. For your convenience the returned function passes the received promise through.

### Rewired.MakeRewired & Rewired.MakeModuleRewiring

The MakeRewired & MakeModuleRewiring Functors allow you to create a custom Rewire module tailerd to your Javscript module's API.


<br />

EXAMPLES IN REASONML
---

## Example #1 : Basic Use Case

The following is the basic use case.
In this use case the following approach is being taken:
- `Rewire.rewire` is called with a local module file being rewired at `./testAsset.js`.
- A global variable in the `testAsset` is then overridden using the `Rewire.set` API which takes the rewired module, the name of the variable being overridden and the mock value.
- The mock value is a JS object created using Bucklescript's jsConverter generator.
- As the rewiredModule only has the Rewire API we then need to use some Raw JS to trick the Reason compiler into letting us call the 'getParam' within the testAsset module.

### testAsset.js
The module we wish to rewire
```javascript
/*
 * This module returns a simple object: { param: "someValue" }
 */
let someModule = require('./someModule.js'); 

module.exports = {
  getParam: function () {
    return someModule.param;
  }
};
```
### Test.re
The test file which uses rewire to test the testAsset.js file
```reason
open Jest;

[@bs.deriving jsConverter]
type oneParamModule = {param: string};

describe("testAsset.getParam", () => {
  open Expect;

  let getParam = [%raw
    {|
          function(rewiredModule) {
            return rewiredModule.getParam();
          }
        |}
  ];

  test("getParam returns the value in the global `someModule.param`", () => {
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

## Example #2 : Custom JS API of module using MakeModuleRewiring & MakeRewired
The downside to Example #1 is that we have to use Raw JS to trick the compiler.
This means our tests are no longer type safe - seems to defeat the purpose of using ReasonML, doesn't it?

### MakeRewired
Start by defining a custom API which mirrors the API of the JS module you're testing.
If we take our testAsset.js as an example, we have a single function, `getParam`, which returns a string.
```reason
module TestAssetModule = {
  include
    MakeRewired(
      {
        type t;
      },
    );
  [@bs.send] external getParam : t => string = "";
};
```
Using `MakeRewired` allows us to define out single function on our module and extend this module with the Rewire API.

### MakeModuleRewiring
Now that we have a type which mirrors our JS module, we can use `MakeModuleRewiring` to create a custom 'Rewire.rewire()' function which will return our custom module type.
This makes it possible for us to call `getParam` directly.

```reason
open Jest;

open Rewire;

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

describe("testAsset.getParam", () =>
  Expect.(
    test(
      "getParam returns the value in the global `someModule.param`",
      () => {
      let rewiredModule = TestAssetRewirting.rewire("./assets/testAsset.js");
      expect(TestAssetModule.getParam(rewiredModule))
      |> toEqual("someValue");
    })
  )
);
```

See [the tests](https://github.com/gmmorris/bs-rewire/tree/master/__tests__) for more examples.

