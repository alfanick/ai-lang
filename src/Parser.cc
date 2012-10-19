#include "Parser.h"

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

  std::string Parser::parse(std::vector<token> tokens) {
    //std::vector<token> tokens = Tokenizer::getInstance().tokenizeCommand(command);
    Tokenizer::print(tokens);
    return "ok";
  }

  void Parser::loop() {
    std::string inputBuffer, buffer;
    std::vector<token> tokens;
    
    int delta;

    std::ios::sync_with_stdio(false);

    
    do {
      tokens.clear();
      buffer.clear();
      delta = 0;
      
      do {
        (*this->outputStream) << ">>> ";
        
        for (int i = 0; i < delta; i++) {
          (*this->outputStream) << "  ";
        }

        std::getline(*this->inputStream, inputBuffer, '\n');
        
        buffer += inputBuffer;
        
        tokens = Tokenizer::getInstance().tokenizeCommand(inputBuffer);
        
        for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
          switch (it->type) {
            case T_LB: case T_LC: case T_LS: delta += 1; break;
            case T_RB: case T_RC: case T_RS: delta -= 1; break;
            default: delta += 0;
          }
        }
        
        tokens = Tokenizer::getInstance().tokenizeCommand(buffer + ";");
      } while (delta != 0);
        
      (*this->outputStream) << this->parse(tokens) << '\n';
    } while (!this->inputStream->eof());
  }
};

