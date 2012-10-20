#include "Element.h"

namespace AI {
  Element::Element(std::vector<token> tokens) {
    Tokenizer::print(tokens);
    for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {

    }
  }

  std::string Element::eval(Context *localContext) {
    return "OK";
  }
};
