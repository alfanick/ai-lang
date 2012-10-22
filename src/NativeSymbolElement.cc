#include "NativeSymbolElement.h"

namespace AI {
	Element* NativeSymbolElement::eval(Context* localContext) {
		return this->body(localContext);
	}

	NativeSymbolElement::~NativeSymbolElement() {

	};
};
