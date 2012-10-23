#ifndef AI_ELEMENT_FILE
#define AI_ELEMENT_FILE

#include <vector>

#include "AILang.h"
#include "Tokenizer.h"

namespace AI {
  class Context;
  /**
   * Basic element in parsing tree.
   */
  class Element {
    public:
      /**
       * For given context evaluates element.
       *
       * For Element return itself - basic Element is a leaf.
       */
      virtual Element* eval(Context*);

      /**
       * Return human readable value of Element.
       */
      virtual std::string value();

      /**
       * Destructor.
       */
      virtual ~Element();
  };
};


#endif
