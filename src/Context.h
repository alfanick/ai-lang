#ifndef AI_CONTEXT_FILE
#define AI_CONTEXT_FILE

#include <map>
#include <string>

#include "AILang.h"

namespace AI {
  class Element;
  /**
   * Symbols context.
   *
   * Database of defined symbols. Each variable or function
   * must belong to context.
   */
  class Context : public std::map<std::string, Element*> {
    public:
      /**
       * Parent context
       */
      Context *parentContext;

      /**
       * Creates blank context
       */
      Context();

      /**
       * Creates context with given parent
       */
      Context(Context*);

      /**
       * Destroy context and its mappings
       */
      ~Context();

      /**
       * Set symbol to given element.
       *
       * If symbol is found in local context then
       * it is modified, otherwise if symbol is found
       * in any parent element, then its modified, else
       * symbol is added to local context.
       *
       * If symbol in system context tried to be modified
       * exception SystemSymbolContextException is thrown.
       *
       * Return context where symbol was put.
       */
      Context* setSymbol(std::string, Element*);

      /**
       * Return symbol for given string.
       *
       * Traverse whole tree for symbol
       */
      Element* getSymbol(std::string);
  };
};

#endif
