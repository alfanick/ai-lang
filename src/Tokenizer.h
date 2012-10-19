#ifndef AI_TOKENIZER_FILE
#define AI_TOKENIZER_FILE

#include <string>
#include <vector>

namespace AI {
  enum token_type {T_NUMBER, T_STRING, T_SYMBOL, T_OPERATOR, T_LB, T_RB, T_SEMICOLON};
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
    void* data;
  };

  class Tokenizer {
    public:
      std::vector<token> tokenizeCommand(std::string);

      static Tokenizer& getInstance() {
        static Tokenizer instance;
        return instance;
      }

    private:
      token createToken(token_type, void*);

      token createNumber(std::string);
      token createString(std::string);
      token createSymbol(std::string);
      token createOperator(std::string);
  };
};

#endif
