#ifndef AI_NATIVESYMBOLELEMENT_FILE
#define AI_NATIVESYMBOLELEMENT_FILE

#include "SymbolElement.h"

namespace AI {
  /**
   * Native symbol elements connects native C/C++ function
   * to symbol in interpreter.
   */
	class NativeSymbolElement : public SymbolElement {
		public:
      /**
       * Constructor. Sets name and function.
       *
       * Native function accepts Context with arguments and must
       * return Element.
       */
			NativeSymbolElement(std::string symbol, Element* (*body)(Context*)) : SymbolElement(symbol) {
				this->body = body;
				this->symbol = symbol;
			};

      /**
       * Simply executes native function in given Context.
       */
			virtual Element* eval(Context*);

      /**
       * Destructor.
       */
			virtual ~NativeSymbolElement();

      /**
       * Pointer to native function.
       */
			Element* (*body)(Context*);
	};
};

#endif
