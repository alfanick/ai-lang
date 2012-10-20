#ifndef AI_ELEMENT_FILE
#define AI_ELEMENT_FILE

#include <vector>

#include "AILang.h"
#include "Tokenizer.h"

namespace AI {
  class Context;
  class Element {
    public:
      Element(std::vector<token>);

      std::string eval(Context*);
    protected:
      std::vector<Element> flow;
  };
};


#endif
