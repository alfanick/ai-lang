#include "Parser.h"
#include "Tokenizer.h"

namespace AI {
  Parser::Parser(std::istream & in, std::ostream& out) {
    this->inputStream = &in;
    this->outputStream = &out;

    this->systemContext = new Context();
    this->globalContext = new Context();
  }

  Parser::~Parser() {
    delete this->globalContext;
    delete this->systemContext;
  }

  std::string Parser::parse(std::string command) {
    std::vector<token> tokens = Tokenizer::getInstance().tokenizeCommand(command);
    return "ok";
  }

  void Parser::loop() {
    std::string inputBuffer;

    std::ios::sync_with_stdio(false);

    do {
      (*this->outputStream) << ">>> ";

      std::getline(*this->inputStream, inputBuffer, ';');

      (*this->outputStream) << this->parse(inputBuffer) << '\n';
    } while (!this->inputStream->eof());
  }
};

