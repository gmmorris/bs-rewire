type rewiringCallback = unit => unit;

type rewiringAsyncCallback('x) = unit => Js.Promise.t('x);

type rewiringExecutor = rewiringCallback => unit;

type rewiringAsyncExecutor('x) =
  rewiringAsyncCallback('x) => Js.Promise.t('x);

type reset = unit => unit;

module type RewiredModule = {
  type t;
  let set: (t, string, 'b) => reset;
  let setAll: (t, Js.Dict.t('b)) => reset;
  let get: (t, string) => 'b;
  let withRewiring: (t, Js.Dict.t('b)) => rewiringExecutor;
  let withRewiringOver: (t, string, 'b) => rewiringExecutor;
  let withAsyncRewiring: (t, Js.Dict.t('b)) => rewiringAsyncExecutor('x);
  let withAsyncRewiringOver: (t, string, 'b) => rewiringAsyncExecutor('x);
};

module MakeRewired = (T: {type t;}) : (RewiredModule with type t = T.t) => {
  type t = T.t;
  [@bs.send] external set : (T.t, string, 'b) => reset = "__set__";
  [@bs.send] external setAll : (T.t, Js.Dict.t('b)) => reset = "__set__";
  [@bs.send] external get : (T.t, string) => 'b = "__get__";
  [@bs.send]
  external withRewiring : (T.t, Js.Dict.t('b)) => rewiringExecutor =
    "__with__";
  [@bs.send]
  external withAsyncRewiring :
    (T.t, Js.Dict.t('b)) => rewiringAsyncExecutor('x) =
    "__with__";
  let withRewiringOver = (rewiredModule: T.t, key: string, value: 'b) => {
    let all = Js.Dict.empty();
    Js.Dict.set(all, key, value);
    withRewiring(rewiredModule, all);
  };
  let withAsyncRewiringOver = (rewiredModule: T.t, key: string, value: 'b) => {
    let all = Js.Dict.empty();
    Js.Dict.set(all, key, value);
    withAsyncRewiring(rewiredModule, all);
  };
};

module MakeModuleRewiring = (T: {type t;}) => {
  [@bs.module] external rewire : string => T.t = "";
};

module Rewired = {
  include
    MakeRewired(
      {
        type t;
      },
    );
};

include MakeModuleRewiring(Rewired);