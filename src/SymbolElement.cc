#include "SymbolElement.h"

namespace AI {
	SymbolElement::SymbolElement(std::string symbol) {
		this->symbol = symbol;
	}

	Element* SymbolElement::eval(Context* localContext) {
		Element* result = localContext->getSymbol(this->symbol);

		if (result == NULL) {
			throw UnknownSymbolContextException(this->symbol);
		}

		return result;
	}

	std::string SymbolElement::value() {
		return this->symbol;
	}

	SymbolElement::~SymbolElement() {
	}
};
