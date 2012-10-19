#include "Parser.h"

namespace AI {
  Parser::Parser(std::istream & in, std::ostream& out) {
    this->inputStream = &in;
    this->outputStream = &out;

    this->systemContext = new Context();
    this->masterContext = new Context();
  }

  Parser::~Parser() {
    delete this->masterContext;
    delete this->systemContext;
  }

  void Parser::loop() {
    (*this->outputStream) << "Hello, world!";
  }
};

