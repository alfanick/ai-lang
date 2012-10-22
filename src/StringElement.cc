#include "StringElement.h"

namespace AI {
  StringElement::StringElement(std::string data) : Element() {
    this->st_value = data;
  };

  StringElement::~StringElement() {
  }

  StringElement* StringElement::eval(Context *localContext) {
    return this;
  }

  std::string StringElement::value() {
    return st_value;
  }

};
