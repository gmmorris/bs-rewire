type rewired;

[@bs.send] external set : (rewired, string, 'a) => unit = "__set__";

[@bs.send] external setAll : (rewired, Js.Dict.t('a)) => unit = "__set__";

[@bs.send] external get : (rewired, string) => 'a = "__get__";

type rewiringCallback = unit => unit;

type rewiringAsyncCallback('a) = unit => Js.Promise.t('a);

type rewiringExecutor = rewiringCallback => unit;

type rewiringAsyncExecutor('a) =
  rewiringAsyncCallback('a) => Js.Promise.t('a);

[@bs.send]
external withRewiring : (rewired, Js.Dict.t('a)) => rewiringExecutor =
  "__with__";

[@bs.send]
external withAsyncRewiring :
  (rewired, Js.Dict.t('a)) => rewiringAsyncExecutor('b) =
  "__with__";

[@bs.module] external rewire : string => rewired = "";