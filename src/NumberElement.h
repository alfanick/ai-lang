#ifndef AI_NUMBERELEMENT_FILE
#define AI_NUMBERELEMENT_FILE

#include <gmp.h>
#include <gmpxx.h>

#include "StringElement.h"

namespace AI {
  /**
   * Creates number representation.
   * GNU MP library float is used (1024 bits of precision).
   */
  class NumberElement : public StringElement {
    public:
      /**
       * Constructor. Creates new number using given string form.
       */
      NumberElement(std::string);

      /**
       * Returns itself, because it is a leaf.
       */
      virtual NumberElement* eval(Context*);

      /**
       * Returns string form of number represented.
       */
      virtual std::string value();

      /**
       * Destructor.
       */
      virtual ~NumberElement();

      /**
       * GNU MP float.
       */
      mpf_class* mp_value;

      /**
       * Creates new NumberElement using given
       * GNU MP float as value.
       */
      static NumberElement* create(mpf_class mp) {
        NumberElement* n = new NumberElement("0");
        delete n->mp_value;
        n->mp_value = new mpf_class(mp);

        return n;
      }
  };
};

#endif
