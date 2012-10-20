#include "Element.h"
#include <iostream>
namespace AI {
  Element::Element(std::vector<token> tokens) {
    // context level
    int level = 0;
    // current instruction tokens
    std::vector<token> currentTokens;

    // foreach token
    for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
      // push current token
      currentTokens.push_back(*it);

      if (it->type == T_SEMICOLON && level == 0) {
        Tokenizer::print(currentTokens);
        std::cout << "\n\n";

        // clear current tokens
        currentTokens.clear();
      } else {
        // check for context change
        switch (it->type) {
          // deeper context
          case T_LB: case T_LC: case T_LS: level += 1; break;
          // shallower context
          case T_RB: case T_RC: case T_RS: level -= 1; break;
          // nop
          default: level += 0;
        }
      }
    }
  }

  std::string Element::eval(Context *localContext) {
    return "OK";
  }
};
