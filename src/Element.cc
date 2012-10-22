#include "Element.h"
#include <iostream>
namespace AI {

  Element* Element::eval(Context* localContext) {
    return new Element();
  }

  std::string Element::value() {
    return "NO OPERATION";
  }

  Element::~Element() {

  }
};
