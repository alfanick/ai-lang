#ifndef AI_NATIVESYMBOLELEMENT_FILE
#define AI_NATIVESYMBOLELEMENT_FILE

#include "SymbolElement.h"

namespace AI {
	class NativeSymbolElement : public SymbolElement {
		public:
			NativeSymbolElement(std::string symbol, Element* (*body)(Context*)) : SymbolElement(symbol) {
				this->body = body;
				this->symbol = symbol;
			};

			virtual Element* eval(Context*);

			virtual ~NativeSymbolElement();

			//std::string symbol;
			Element* (*body)(Context*);
			//Context *context;
	};
};

#endif
