#ifndef AI_DEFINITIONSYMBOLELEMENT_FILE
#define AI_DEFINITIONSYMBOLELEMENT_FILE

#include "Element.h"
#include "SymbolElement.h"

namespace AI {
	class DefinitionSymbolElement : public SymbolElement {
		public:
			DefinitionSymbolElement(std::string symbol) : SymbolElement(symbol) { };

			virtual Element* eval(Context*);
			virtual std::string value();

			virtual ~DefinitionSymbolElement();

			void injectFlow(std::vector<Element*>);

			//std::string symbol;
			std::vector<Element*> body;
			//Context *context;
	};
};

#endif
