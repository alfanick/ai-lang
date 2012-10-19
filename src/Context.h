#ifndef AI_CONTEXT_FILE
#define AI_CONTEXT_FILE

#include <map>
#include <string>

#include "AILang.h"

namespace AI {
  class Element;
  class Context : public std::map<std::string, Element*> {
    public:
      ~Context();
  };
};

#endif
