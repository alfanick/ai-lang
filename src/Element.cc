#include "Element.h"
#include <iostream>
namespace AI {
  std::string OPERATORS[] = { "||", "&&", "|", "^", "&", "!=", "==", ">=", ">", "<=", "<", ">>", "<<", "-", "+", "%", "/", "*", "!", "~"};
  std::string OPERATORS_FUNC[] = { "operator.or", "operator.and", "operator.bit_or", "operator.bit_xor", "operator.bit_and",
                                   "operator.not_equal", "operator.equal", "operator.greater_equal", "operator.greater", "operator.less_equal", "operator.less",
                                   "operator.bit_shift_right", "operator.bit_shift_left", "operator.subtract", "operator.add",
                                   "operator.modulo", "operator.divide", "operator.multiply", "operator.not", "operator.bit_not" };
  int OPERATORS_COUNT = 20;

  Element::Element(std::vector<token> tokens) {
    // context level
    int level = 0;
    // current instruction tokens
    std::vector<token> currentTokens;

    // foreach token
    for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
      // push current token
      if (it->type != T_NOP && it->type != T_BEGIN)
        currentTokens.push_back(*it);

      if ((it->type == T_SEMICOLON || it->type == T_COMMA) && level == 0) {
        int currentLevel = 0;
        int currentPosition = 0;

        // minify brackets
        bool ok = false;
        std::vector<token>::iterator a, b;
        do {
          for (std::vector<token>::iterator ct = currentTokens.begin(); ct != currentTokens.end(); ct++) {
            // zaczyna sie i konczy nawiasem, ale bez ich zmiany
            if (ct->type == T_LB) {
              if (currentLevel == 0) {
                a = ct;
              }
              ok = true;
              currentLevel++;
            } else if (ct->type == T_RB) {
              currentLevel--;
              ok = true;
              if (currentLevel == 0) {
                b = ct;
              }
            } else if (currentLevel == 0 && ct->type != T_SEMICOLON) {
              ok = false;
              break;
            }
          }

          if (ok) {
            currentTokens.erase(b);
            currentTokens.erase(a);
          }
        } while (ok);

        currentLevel = 0;

        Tokenizer::print(currentTokens);
        std::cout << "\n\n";
        bool maybeFunction = false;
        int operationIndex = OPERATORS_COUNT;
        int operationPosition = -1;
        for (std::vector<token>::iterator ct = currentTokens.begin(); ct != (currentTokens.end()-1); ct++) {
          if (ct->type == T_LB)
            currentLevel++;
          else if (ct->type == T_RB)
            currentLevel--;

          if (currentPosition == 0 && ct->type == T_NUMBER && (ct+1)->type == T_SEMICOLON) {
            std::cerr << "pojedyncza liczba;\n";
          } else
          if (currentPosition == 0 && ct->type == T_STRING && (ct+1)->type == T_SEMICOLON) {
            std::cerr << "pojedynczy napis\n";
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && ((ct+1)->type == T_OPERATOR && (ct+1)->data == "=")) {
            std::cerr << "przypiasanie zmiennej;\n";
            break;
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && (ct+1)->type == T_SEMICOLON) {
            std::cerr << "wywolanie zmiennej;\n";
            break;
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && (ct+1)->type == T_LB) {
            maybeFunction = true;
          } else
          if (currentLevel == 0 && ct->type == T_RB && maybeFunction) {
            if ((ct+1)->type == T_SEMICOLON) {
              std::cerr << "wykonanie funkcji\n";
            } else
            if ((ct+1)->type == T_OPERATOR && (ct+1)->data == "=") {
              std::cerr << "przypisanie funkcji\n";
            }
            break;
          } else
          if (currentLevel == 0) {
            if (ct->type == T_OPERATOR) {
              int index = -1;
              for (index = 0; index < OPERATORS_COUNT; index++) {
                if (ct->data == OPERATORS[index]) {
                  break;
                }
              }

              if (index < operationIndex) {
                operationIndex = index;
                operationPosition = ct - currentTokens.begin();
              }
              //break;
            }
          }

          if (ct->type != T_NOP && ct->type != T_BEGIN)
            currentPosition++;
        }

        if (operationIndex != OPERATORS_COUNT) {
          std::cerr << "dzialanie " << OPERATORS_FUNC[operationIndex] << "(<0,"<< operationPosition-1 <<">, <"<< operationPosition+1 <<","<< currentTokens.size()-2 <<">)\n";
        }

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
