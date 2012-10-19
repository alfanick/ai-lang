#ifndef AI_CONTEXT_FILE
#define AI_CONTEXT_FILE

#include <map>
#include <string>

#include "Element.h"

namespace AI {
  class Context : public std::map<std::string, Element*> {
    public:
      ~Context();
  };
};

#endif
