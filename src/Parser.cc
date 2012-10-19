#include "Parser.h"

namespace AI {
  Parser::Parser(std::istream & in, std::ostream& out) {
    this->inputStream = &in;
    this->outputStream = &out;

    this->systemContext = new Context();
    this->globalContext = new Context();
    
    this->tokenizer = new Tokenizer();
    this->root = NULL;
  }

  Parser::~Parser() {
    if (this->root != NULL)
      delete this->root;
    delete this->tokenizer;
    delete this->globalContext;
    delete this->systemContext;
  }

  Element *Parser::parse(std::vector<token> tokens) {
    if (this->root != NULL)
      delete this->root;
    this->root = new Element();
    
    this->tokenizer->print(tokens);
    
    return this->root;
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
        
        tokens = this->tokenizer->tokenizeCommand(inputBuffer);
        
        for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
          switch (it->type) {
            case T_LB: case T_LC: case T_LS: delta += 1; break;
            case T_RB: case T_RC: case T_RS: delta -= 1; break;
            default: delta += 0;
          }
        }
        
        tokens = this->tokenizer->tokenizeCommand(buffer + ";");
      } while (delta != 0);
        
      (*this->outputStream) << this->parse(tokens)->eval(this->globalContext) << '\n';
    } while (!this->inputStream->eof());
  }
};

