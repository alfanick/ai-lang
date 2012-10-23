#ifndef AI_DEFINITIONSYMBOLELEMENT_FILE
#define AI_DEFINITIONSYMBOLELEMENT_FILE

#include "Element.h"
#include "SymbolElement.h"

namespace AI {
  /**
   * Definition of function.
   *
   * Function is defined by its name, body and arguments.
   */
	class DefinitionSymbolElement : public SymbolElement {
		public:
      /**
       * Constructor. Initializes name and context.
       */
			DefinitionSymbolElement(std::string symbol) : SymbolElement(symbol) { };

      /**
       * Evaluates value of function for given context.
       */
			virtual Element* eval(Context*);

      /**
       * Not evaluated value - name
       */
      virtual std::string value();

      /**
       * Destructor. Removes commands for body flow.
       */
			virtual ~DefinitionSymbolElement();

      /**
       * Injects flow of arguments.
       *
       * For each argument symbol, it is
       * put to localContext with value at its position.
       */
			void injectFlow(std::vector<Element*>);

      /**
       * Body flow. Vector of elements evaluated sequentially.
       */
			std::vector<Element*> body;
	};
};

#endif
