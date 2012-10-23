#include "DefinitionSymbolElement.h"
#include <iostream>
namespace AI {

	Element* DefinitionSymbolElement::eval(Context* localContext) {
		this->context->parentContext = localContext;

		Element *result = new Element();
		for (std::vector<Element*>::iterator command = this->body.begin(); command != this->body.end(); command++) {
			result = (*command)->eval(this->context);
		}

		this->context->parentContext = NULL;

		return result;
	}

	void DefinitionSymbolElement::injectFlow(std::vector<Element*> flow) {
		int argumentNumber = 0;
		for (std::vector<Element*>::iterator argument = flow.begin(); argument != flow.end(); argument++) {
			std::ostringstream s;

			s << "$" << argumentNumber;
			this->context->setSymbol((*argument)->value(), new SymbolElement(s.str()));

			argumentNumber++;
		}
	}

	std::string DefinitionSymbolElement::value() {
		return this->symbol;
	}

	DefinitionSymbolElement::~DefinitionSymbolElement() {
		while (!this->body.empty()) {
			delete this->body.back();
			this->body.pop_back();
		}
		delete this->context;
	}
};
