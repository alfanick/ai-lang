#ifndef AI_SYMBOLELEMENT_FILE
#define AI_SYMBOLELEMENT_FILE

#include <sstream>

#include "Element.h"
#include "Context.h"

namespace AI {
	class SymbolElement : public Element {
		public:
			SymbolElement(std::string);

			virtual Element* eval(Context*);
			virtual std::string value();

			virtual ~SymbolElement();

			void injectFlow(std::vector<Element*>);

			std::string symbol;
			Context *context;
	};
};

#endif
