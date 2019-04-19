#include "options.h"

namespace Morphine {

  string Options::getOption(string option) {
    return options[option];
  }

  void Options::setOption(string option, string value) {
    options[option] = value;
  }

}