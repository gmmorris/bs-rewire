type rewiringCallback = unit => unit;
type rewiringAsyncCallback('x) = unit => Js.Promise.t('x);
type rewiringExecutor = rewiringCallback => unit;
type rewiringAsyncExecutor('x) =
    rewiringAsyncCallback('x) => Js.Promise.t('x);
type reset = unit => unit;
module type RewiredModule =
  {
    type t;
    let set: (t, string, 'b) => reset;
    let setAll: (t, Js.Dict.t('b)) => reset;
    let get: (t, string) => 'b;
    let withRewiring: (t, Js.Dict.t('b)) => rewiringExecutor;
    let withAsyncRewiring: (t, Js.Dict.t('b)) => rewiringAsyncExecutor('x);
  };
module MakeRewired:
  (T : { type t; }) => {
                         type t = T.t;
                         let set: (t, string, 'b) => reset;
                         let setAll: (t, Js.Dict.t('b)) => reset;
                         let get: (t, string) => 'b;
                         let withRewiring:
                           (t, Js.Dict.t('b)) => rewiringExecutor;
                         let withAsyncRewiring:
                           (t, Js.Dict.t('b)) => rewiringAsyncExecutor('x);
                       };
module MakeModuleRewiring:
  (T : { type t; }) => { let rewire: string => T.t; };
module Rewired:
  {
    type t;
    let set: (t, string, 'b) => reset;
    let setAll: (t, Js.Dict.t('b)) => reset;
    let get: (t, string) => 'b;
    let withRewiring: (t, Js.Dict.t('b)) => rewiringExecutor;
    let withAsyncRewiring: (t, Js.Dict.t('b)) => rewiringAsyncExecutor('x);
  };
let rewire: string => Rewired.t;
