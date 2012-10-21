#ifndef AILANG_INCLUDED
#define AILANG_INCLUDED

#include <string>
#include <exception>

#include "Element.h"
#include "Context.h"
#include "Tokenizer.h"
#include "Parser.h"

namespace AI {
  class Element;
  class Context;
  class Tokenizer;
  class Parser;

  class Exception : public std::exception { };
  class ParserException : public Exception { };
  class UnexpectedCharacterParserException : public ParserException {
    public:
      char uc;
      int pos;
      UnexpectedCharacterParserException(char uc, int pos) : ParserException() {
        this->uc = uc;
        this->pos = pos;
      }

      ~UnexpectedCharacterParserException() throw() { };
  };
  class UnexpectedOperatorParserException : public ParserException {
    public:
      std::string op;
      int pos;
      UnexpectedOperatorParserException(std::string op, int pos) : ParserException() {
        this->op = op;
        this->pos = pos;
      }

      ~UnexpectedOperatorParserException() throw() { };
  };
};

#endif
