#ifndef AI_ELEMENT_FILE
#define AI_ELEMENT_FILE

#include <vector>

#include "AILang.h"
#include "Tokenizer.h"

namespace AI {
  class Context;
  class Element {
    public:
      virtual Element* eval(Context*);
      virtual std::string value();

      virtual ~Element();
  };
};


#endif
