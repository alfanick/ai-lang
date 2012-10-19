#include "Context.h"

namespace AI {
  Context::~Context() {
    for (std::map<std::string, Element*>::iterator it = this->begin(); it != this->end(); it++) {
      delete it->second;
    }

    this->clear();
  }
};
