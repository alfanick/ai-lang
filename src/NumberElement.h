#ifndef AI_NUMBERELEMENT_FILE
#define AI_NUMBERELEMENT_FILE

#include <gmp.h>
#include <gmpxx.h>

#include "StringElement.h"

namespace AI {
  class NumberElement : public StringElement {
    public:
      NumberElement(std::string);

      virtual NumberElement* eval(Context*);
      virtual std::string value();

      virtual ~NumberElement();

      mpf_class* mp_value;

      static NumberElement* create(mpf_class mp) {
        NumberElement* n = new NumberElement("0");
        delete n->mp_value;
        n->mp_value = new mpf_class(mp);

        return n;
      }
  };
};

#endif
