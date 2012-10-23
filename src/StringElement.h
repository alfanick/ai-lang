#ifndef AI_STRINGELEMENT_FILE
#define AI_STRINGELEMENT_FILE

#include <string>

#include "Element.h"

namespace AI {
  /**
   * String element
   */
  class StringElement : public Element {
    public:
      /**
       * Constructor. Sets value to given string.
       */
      StringElement(std::string);

      /**
       * Return itself (StringElement is a leaf in a parsing tree.).
       */
      virtual StringElement* eval(Context*);

      /**
       * Return string value.
       */
			virtual std::string value();

      /**
       * Destructor.
       */
      virtual ~StringElement();

		protected:
      // String value
      std::string st_value;
  };
};

#endif

