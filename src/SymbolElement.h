#ifndef AI_SYMBOLELEMENT_FILE
#define AI_SYMBOLELEMENT_FILE

#include <sstream>

#include "Element.h"
#include "Context.h"

namespace AI {
  /**
   * Symbol elements reprent symbol evaluation.
   */
	class SymbolElement : public Element {
		public:
      /**
       * Creates SymbolElement with given name.
       */
      SymbolElement(std::string);

      /**
       * Evaluates symbol.
       *
       * If symbol is a variable, then it is evaluated in given context
       * and returned.
       * If symbol is a function, then function is evaluated in given context
       * with injected arguments and then it is returned.
       */
			virtual Element* eval(Context*);

      /**
       * Name of symbol
       */
			virtual std::string value();

      /**
       * Destructor. Destroys arguments context.
       */
			virtual ~SymbolElement();

      /**
       * Injects arguments flow.
       *
       * For each evaluated form of argument it is assigned
       * to given position variable. Then using these variables
       * proper symbol names are given.
       */
			void injectFlow(std::vector<Element*>);

      /**
       * Name of symbol.
       */
			std::string symbol;

      /**
       * Arguments and evaluation context.
       */
			Context *context;
	};
};

#endif
