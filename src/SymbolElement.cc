#include "SymbolElement.h"

namespace AI {
	SymbolElement::SymbolElement(std::string symbol) {
		this->symbol = symbol;
		this->context = new Context();
	}

	Element* SymbolElement::eval(Context* localContext) {
		this->context->parentContext = localContext;

		Element* result = this->context->getSymbol(this->symbol);

		if (result == NULL) {
			throw UnknownSymbolContextException(this->symbol);
		}

		result = result->eval(this->context);

		//if (this->argumentsFlow.size() > 0 && result->argumentsFlow.size() == 0) {
		//	throw NotFunctionContextException(this->symbol);
		//}

		this->context->parentContext = NULL;

		return result;
	}

	void SymbolElement::injectFlow(std::vector<Element*> flow) {
		int argumentNumber = 0;
		for (std::vector<Element*>::iterator argument = flow.begin(); argument != flow.end(); argument++) {
			std::ostringstream s;

			s << "$" << argumentNumber;

			this->context->setSymbol(s.str(), *argument);

			argumentNumber++;
		}
	}

	std::string SymbolElement::value() {
		return this->symbol;
	}

	SymbolElement::~SymbolElement() {
		delete this->context;
	}
};
