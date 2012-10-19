#include "Tokenizer.h"

#include <iostream>


namespace AI {
  std::string OPERATORS_L[] = {"<<=", ">>=", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||", "*=", "/=", "%=", "+=", "-=","&=", "^=", "|=", "=", "&", "^", "|", "<", ">", "~", "!", "-", "=", "*", "/", "%", "+"};
  int OPERATORS_L_COUNT = 32;
  
  std::vector<token> Tokenizer::tokenizeCommand(std::string command) {
    std::vector<token> tokens;
    
    std::string buffer;
    
    tokens.push_back(this->newToken(T_BEGIN));
    
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
      // Outside of string
      if (currentToken != T_STRING) {
        // If symbol name
        if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || (*it == '$') || (*it == '_')) {
          buffer += *it;
          currentToken = T_SYMBOL;
        } else
        // Number or symbol
        if ((*it >= '0' && *it <= '9') || (*it == '.')) {
          // Continue symbol name
          if (currentToken == T_SYMBOL) {
            buffer += *it;
          }
          // Parse number
          else {
            currentToken = T_NUMBER;
            buffer += *it;
          }
        } else {
          // End of symbol
          if (currentToken == T_SYMBOL) {
            tokens.push_back(this->createSymbol(buffer));
          } else
          // End of number
          if (currentToken == T_NUMBER) {
            tokens.push_back(this->createNumber(buffer));
          }
          
          buffer.clear();
          currentToken = T_UNKNOWN;
          
          // Brackets parsing
          if (*it == '(') {
            tokens.push_back(this->newToken(T_LB));
          } else
          if (*it == ')') {
            tokens.push_back(this->newToken(T_RB));
          } else
          if (*it == '{') {
            tokens.push_back(this->newToken(T_LC));
          } else
          if (*it == '}') {
            tokens.push_back(this->newToken(T_RC));
          } else
          if (*it == '[') {
            tokens.push_back(this->newToken(T_LS));
          } else
          if (*it == ']') {
            tokens.push_back(this->newToken(T_RS));
          } else
          // Arguments comma
          if (*it == ',') {
            tokens.push_back(this->newToken(T_COMMA));
          }
          // Operators
          else {
            std::string op;
            for (int i = 0; i < OPERATORS_L_COUNT; i++) {
              op = OPERATORS_L[i];
              
              if (std::string(it, command.end()).find(op) == 0) {
                tokens.push_back(this->createOperator(op));
                it += op.length()-1;
                break;
              }
            }
          }
        }
      }
    }
    
    // Negative numbers
    if (tokens.size() >= 3) {
      for (std::vector<token>::iterator it = tokens.begin()+1; it != tokens.end()-1; it++) {
        if ((it+1)->type == T_NUMBER) {
          if ((it-1)->type == T_COMMA || (it-1)->type == T_LB || (it-1)->type == T_LC || (it-1)->type == T_LS || (it-1)->type == T_BEGIN) {
            if (it->type == T_OPERATOR && it->data == "-") {
              it->type = T_NOP;
              (it+1)->data.insert(0, "-");
            }
          }
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
  
  token Tokenizer::createSymbol(std::string data) {
    return this->newToken(T_SYMBOL, data);
  }
  
  token Tokenizer::createNumber(std::string data) {
    return this->newToken(T_NUMBER, data);
  }
  
  token Tokenizer::createOperator(std::string data) {
    return this->newToken(T_OPERATOR, data);
  }
};
