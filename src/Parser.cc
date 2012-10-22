#include "Parser.h"
#include "StringElement.h"
#include "NumberElement.h"
#include "SymbolElement.h"

namespace AI {
  std::string OPERATORS[] = { "||", "&&", "|", "^", "&", "!=", "==", ">=", ">", "<=", "<", ">>", "<<", "-", "+", "%", "/", "*", "!", "~"};
  std::string OPERATORS_FUNC[] = { "operator.or", "operator.and", "operator.bit_or", "operator.bit_xor", "operator.bit_and",
                                   "operator.not_equal", "operator.equal", "operator.greater_equal", "operator.greater", "operator.less_equal", "operator.less",
                                   "operator.bit_shift_right", "operator.bit_shift_left", "operator.subtract", "operator.add",
                                   "operator.modulo", "operator.divide", "operator.multiply", "operator.not", "operator.bit_not" };
  int OPERATORS_COUNT = 20;

  Parser::Parser(std::istream & in, std::ostream& out) {
    this->inputStream = &in;
    this->outputStream = &out;

    this->systemContext = new Context();
    this->globalContext = new Context(this->systemContext);

    this->tokenizer = new Tokenizer();
  }

  Parser::~Parser() {
    while (!this->flow.empty()) {
      delete this->flow.back();
      this->flow.pop_back();
    }
    this->flow.clear();
    delete this->tokenizer;
    delete this->globalContext;
    delete this->systemContext;
  }

  std::vector<Element*> Parser::createFlow(std::vector<token> tokens, Context *localContext) {
    // context level
    int level = 0;
    // current instruction tokens
    std::vector<token> currentTokens;

//    Parser::getInstance().systemContext->setSymbol("system.operator.add", new StaticFunctionElement(&so_add));
//    Parser::getInstance().globalContext->setSymbol("operator.add", Parser::getInstance().systemContext->getSymbol("system.operator.add"));

    std::vector<Element*> currentFlow;
    currentFlow.push_back(new Element());

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
        std::vector<token> tmpTokens;
        std::vector<Element*> tmpFlow;
        for (std::vector<token>::iterator ct = currentTokens.begin(); ct != (currentTokens.end()-1); ct++) {
          tmpTokens.clear();
          tmpFlow.clear();

          if (ct->type == T_LB)
            currentLevel++;
          else if (ct->type == T_RB)
            currentLevel--;

          if (currentPosition == 0 && ct->type == T_NUMBER && (ct+1)->type == T_SEMICOLON) {
            currentFlow.push_back(new NumberElement(ct->data));
            break;
          } else
          if (currentPosition == 0 && ct->type == T_STRING && (ct+1)->type == T_SEMICOLON) {
            currentFlow.push_back(new StringElement(ct->data));
            break;
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && ((ct+1)->type == T_OPERATOR && (ct+1)->data == "=")) {
            tmpTokens.resize(currentTokens.end() - ct - 2);
            std::copy(ct+2, currentTokens.end(), tmpTokens.begin());

            tmpFlow = Parser::createFlow(tmpTokens, localContext);
            localContext->setSymbol(ct->data, tmpFlow.back());
            break;
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && (ct+1)->type == T_SEMICOLON) {
            std::cerr << "wywolanie zmiennej;\n";
            currentFlow.push_back(new SymbolElement(ct->data));
            break;
          } else
          if (currentPosition == 0 && ct->type == T_SYMBOL && (ct+1)->type == T_LB) {
            maybeFunction = true;
          } else
          if (currentLevel == 0 && ct->type == T_RB && maybeFunction) {
            if ((ct+1)->type == T_SEMICOLON) {
              std::cerr << "wykonanie funkcji\n";
              break;
            } else
            if ((ct+1)->type == T_OPERATOR && (ct+1)->data == "=") {
              std::cerr << "przypisanie funkcji\n";
              break;
            }
          }
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

    return currentFlow;
  };

  Element *Parser::parse(std::vector<token> tokens) {
    while (!this->flow.empty()) {
      delete this->flow.back();
      this->flow.pop_back();
    }
    this->flow.clear();

    this->flow = Parser::createFlow(tokens, this->globalContext);

    return this->flow.back();
  }

  void Parser::loop() {
    std::string inputBuffer, buffer;
    std::vector<token> tokens;

    int delta;

    std::ios::sync_with_stdio(false);


    do {
      try {
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

        this->parse(tokens);
        for (std::vector<Element*>::iterator command = this->flow.begin(); command != this->flow.end(); command++) {
          (*this->outputStream) << (*command)->eval(this->globalContext)->value() << '\n';
        }
      }
      catch (UnexpectedCharacterParserException e) {
        (*this->outputStream) << "[ERROR] Unexpected character '" << e.uc << "' at position " << e.pos+1 <<".\n";
      }
      catch (UnexpectedOperatorParserException e) {
        (*this->outputStream) << "[ERROR] Unexpected operator '" << e.op << "' at position " << e.pos+1 << ".\n";
      }
      catch (SystemSymbolContextException e) {
        (*this->outputStream) << "[ERROR] Trying to modify system '" << e.sym << "' symbol.\n";
      }
      catch (UnknownSymbolContextException e) {
        (*this->outputStream) << "[ERROR] Symbol '" << e.sym << "' is unknown.\n";
      }
      catch (Exception e) {
        (*this->outputStream) << "[ERROR] Unknown error.\n";
      }
    } while (!this->inputStream->eof());
  }
};

