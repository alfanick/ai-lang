#ifndef AI_TOKENIZER_FILE
#define AI_TOKENIZER_FILE

#include <string>
#include <vector>

#include <iostream>

namespace AI {
  enum token_type {T_UNKNOWN, T_NUMBER, T_STRING, T_SYMBOL, T_OPERATOR, T_LB, T_RB, T_SEMICOLON, T_COMMA};
  enum token_operator {T_SET, T_EQUAL};

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
     *
     * Data type depends on token type:
     *   - T_NUMBER - mpf_class
     *   - T_STRING - std::string
     *   - T_SYMBOL - std::string
     *   - T_OPERATOR - token_type
     */
    std::string data;
  };

  class Tokenizer {
    public:
      std::vector<token> tokenizeCommand(std::string);

      static Tokenizer& getInstance() {
        static Tokenizer instance;
        return instance;
      }
    
      static void print(std::vector<token> tokens) {
        for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
          switch ((*it).type) {
            case T_NUMBER: std::cerr << "NUMBER"; break;
            case T_STRING: std::cerr << "STRING " << it->data; break;
            case T_SYMBOL: std::cerr << "SYMBOL " << it->data; break;
            case T_OPERATOR: std::cerr << "OPERATOR " << it->data; break;
            case T_LB: std::cerr << "LEFT BRACKET"; break;
            case T_RB: std::cerr << "RIGHT BRACKET"; break;
            case T_SEMICOLON: std::cerr << "SEMICOLON"; break;
            case T_COMMA: std::cerr << "COMMA"; break;
            default: std::cerr << "UNKNOWN("<< it->type <<")"; break;
          }
          
          std::cerr << "\n";
        }
      }

    private:
      token newToken(token_type, std::string);
      token newToken(token_type);

      token createNumber(std::string);
      token createString(std::string);
      token createSymbol(std::string);
      token createOperator(std::string);
  };
};

#endif
