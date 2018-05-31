let someModule = {
  param: "someValue"
};

let someOtherModule = {
  param: "someOtherValue"
};

module.exports = {
  getParam: function () {
    return someModule.param;
  },
  getOtherParam: function () {
    return someOtherModule.param;
  }
};