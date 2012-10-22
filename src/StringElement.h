#ifndef AI_STRINGELEMENT_FILE
#define AI_STRINGELEMENT_FILE

#include <string>

#include "Element.h"

namespace AI {
  class StringElement : public Element {
    public:
      StringElement(std::string);

      virtual StringElement* eval(Context*);
			virtual std::string value();

      virtual ~StringElement();

			std::string st_value;
  };
};

#endif

