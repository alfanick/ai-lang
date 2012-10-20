#ifndef AI_TOKENIZER_FILE
#define AI_TOKENIZER_FILE

#include <string>
#include <vector>

#include <iostream>

namespace AI {
  enum token_type {T_UNKNOWN, T_NUMBER, T_STRING, T_SYMBOL, T_OPERATOR, T_LB, T_RB, T_LC, T_RC, T_LS, T_RS, T_SEMICOLON, T_COMMA, T_NOP, T_BEGIN};
  

  /**
   * Single token structure.
   *
   * Identifies source token.
   */
  struct token {
    /**
     * Describes token function.
     */
    token_type type;

    /**
     * Token data.
     */
    std::string data;
  };

  /**
   * Tokenize string input to tokens.
   */
  class Tokenizer {
    public:
      /**
       * Takes string and returns vector of tokens.
       */
      std::vector<token> tokenizeCommand(std::string);
    
      /**
       * Debugging printer
       */
      static void print(std::vector<token> tokens) {
        for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
          if (it->type == T_NOP || it->type == T_BEGIN)
            continue;
          
          switch (it->type) {
            case T_NUMBER: std::cerr << "NUMBER " << it->data; break;
            case T_STRING: std::cerr << "STRING " << it->data; break;
            case T_SYMBOL: std::cerr << "SYMBOL " << it->data; break;
            case T_OPERATOR: std::cerr << "OPERATOR " << it->data; break;
            case T_LB: case T_LC: case T_LS: std::cerr << "LEFT BRACKET"; break;
            case T_RB: case T_RC: case T_RS: std::cerr << "RIGHT BRACKET"; break;
            case T_SEMICOLON: std::cerr << "SEMICOLON"; break;
            case T_COMMA: std::cerr << "COMMA"; break;
            default: std::cerr << "UNKNOWN("<< it->type <<")"; break;
          }
          
          std::cerr << "\n";
        }
      }

    private:
      // Creates new token with given type and data
      token newToken(token_type, std::string);
      // Creates new token with given type
      token newToken(token_type);

      // Creates new number
      token createNumber(std::string);
      // Creates new string
      token createString(std::string);
      // Creates new symbol
      token createSymbol(std::string);
      // Creates new operator
      token createOperator(std::string);
  };
};

#endif
