#include "Context.h"

namespace AI {
  Context::Context() : std::map<std::string, Element*>() {
    this->parentContext = NULL;
  }

  Context::Context(Context* parentContext) {
    this->parentContext = parentContext;
  }

  Context::~Context() {
    for (std::map<std::string, Element*>::iterator it = this->begin(); it != this->end(); it++) {
      delete it->second;
    }

    this->clear();
  }

  Context* Context::setSymbol(std::string symbolName, Element* value) {
    Context* currentContext = this;
    Context::iterator it;

    do {
      if ((it = currentContext->find(symbolName)) != currentContext->end()) {
        if (currentContext == Parser::getInstance().systemContext && currentContext != this) {
          throw SystemSymbolContextException(symbolName);
        }

        it->second = value;

        break;
      }

      currentContext = currentContext->parentContext;
    } while(currentContext != NULL);

    if (currentContext == NULL) {
      this->insert(std::pair<std::string, Element*>(symbolName, value));
    }

    return currentContext;
  }

  Element* Context::getSymbol(std::string symbolName) {
    Context* currentContext = this;
    Element* result = NULL;
    Context::iterator it;

    do {
      if ((it = currentContext->find(symbolName)) != currentContext->end()) {
        result = it->second;

        break;
      }

      currentContext = currentContext->parentContext;
    } while(currentContext != NULL);

    return result;
  }
};
