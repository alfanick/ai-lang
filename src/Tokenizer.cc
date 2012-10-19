#include "Tokenizer.h"

#include <iostream>

namespace AI {
  std::vector<token> Tokenizer::tokenizeCommand(std::string command) {
    std::vector<token> tokens;
    
    std::string buffer;
    token_type currentToken = T_UNKNOWN;
    
    for (std::string::iterator it = command.begin(); it != command.end(); it++) {
      // String parsing
      if (*it == '\'') {
        // If not parsing string then start
        if (currentToken != T_STRING) {
          currentToken = T_STRING;
        // If parsing string then stop
        } else {
          tokens.push_back(this->createString(buffer));
          buffer.clear();
          currentToken = T_UNKNOWN;
        }
      } else
      // Append string content
      if (currentToken == T_STRING) {
        buffer += *it;
      } else
      if (currentToken != T_STRING) {
        // Brackets parsing
        if (*it == '(') {
          tokens.push_back(this->newToken(T_LB));
        } else
        if (*it == ')') {
          tokens.push_back(this->newToken(T_RB));
        } else
        // Arguments comma
        if (*it == ',') {
          tokens.push_back(this->newToken(T_COMMA));
        }
      }
      
    }
    
    return tokens;
  }
  
  token Tokenizer::newToken(token_type type, std::string data) {
    token t;
    t.type = type;
    t.data = data;
    return t;
  }
  
  token Tokenizer::newToken(token_type type) {
    token t;
    t.type = type;
    return t;
  }
  
  token Tokenizer::createString(std::string data) {
    return this->newToken(T_STRING, data);
  }
};
