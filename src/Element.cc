#include "Element.h"
#include <iostream>
namespace AI {

  Element* Element::eval(Context* localContext) {
    return this;
  }

  std::string Element::value() {
    return "";
  }

  Element::~Element() {

  }
};
