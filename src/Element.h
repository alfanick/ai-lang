#ifndef AI_ELEMENT_FILE
#define AI_ELEMENT_FILE

#include "AILang.h"

namespace AI {
  class Context;
  class Element {
    public:
      std::string eval(Context*);
  };
};


#endif
