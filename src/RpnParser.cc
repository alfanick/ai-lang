#include "Parser.h"
#include "StringElement.h"
#include "NumberElement.h"
#include "SymbolElement.h"
#include "DefinitionSymbolElement.h"
#include "NativeSymbolElement.h"

#include "Operators.h"

#include <stack>

namespace AI {
  std::string OPERATORS[] = { "||", "&&", "|", "^", "&", "!=", "==", ">=", ">", "<=", "<", ">>", "<<", "-", "+", "%", "/", "*", "!", "~"};
  std::string OPERATORS_FUNC[] = { "operator.or", "operator.and", "operator.bit_or", "operator.bit_xor", "operator.bit_and",
                                   "operator.not_equal", "operator.equal", "operator.greater_equal", "operator.greater", "operator.less_equal", "operator.less",
                                   "operator.bit_shift_right", "operator.bit_shift_left", "operator.subtract", "operator.add",
                                   "operator.modulo", "operator.divide", "operator.multiply", "operator.not", "operator.bit_not" };
  int OPERATORS_COUNT = 20;

  namespace Operators {
    Element *(*OPERATORS_NATIVE[])(Context*) = { &o_or, &o_and, &bit_or, &bit_xor, &bit_and,
                                                 &not_equal, &equal, &greater_equal, &greater, &less_equal, &less,
                                                 &bit_shift_right, &bit_shift_left, &subtract, &add,
                                                 &modulo, &divide, &multiply, &o_not, &bit_not };
  };

  Parser::Parser(std::istream & in, std::ostream& out) {
    this->inputStream = &in;
    this->outputStream = &out;

    this->systemContext = new Context();
    this->globalContext = new Context(this->systemContext);

    for (int i = 0; i < OPERATORS_COUNT; i++) {
      this->systemContext->setSymbol("system." + OPERATORS_FUNC[i], new NativeSymbolElement(OPERATORS_FUNC[i], Operators::OPERATORS_NATIVE[i]));
      this->globalContext->setSymbol(OPERATORS_FUNC[i], this->systemContext->getSymbol("system." + OPERATORS_FUNC[i]));
    }

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
    // current instruction tokens
    std::vector<token> currentTokens;

    std::vector<Element*> currentFlow;
    currentFlow.push_back(new Element());

    // foreach token
    for (std::vector<token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
      if (it->type == T_OPERATOR) {
        if (it->data == "=") {
          currentTokens.clear();
          currentTokens.resize(tokens.size());
          copy(tokens.begin(), it-1, currentTokens.begin());
          localContext->setSymbol(currentFlow.back()->value(), Parser::createFlow(currentTokens, localContext).back());
          currentFlow.pop_back();
        } else {
          int index = -1;
          for (index = 0; index < OPERATORS_COUNT; index++)
            if (it->data == OPERATORS[index])
              break;

          SymbolElement *symbol = new SymbolElement(OPERATORS_FUNC[index]);

          if (currentFlow.size() <= 2) {
            throw UnexpectedOperatorParserException(it->data, tokens.end() - it - 1);
          }

          std::vector<Element*> argsFlow;
          argsFlow.push_back(new Element());
          argsFlow.push_back(currentFlow.back()); currentFlow.pop_back();
          argsFlow.insert(argsFlow.end()-1, currentFlow.back()); currentFlow.pop_back();

          symbol->injectFlow(argsFlow);

          currentFlow.push_back(symbol);
        }
      } else
      if (it->type == T_NUMBER) {
        currentFlow.push_back(new NumberElement(it->data));
      } else
      if (it->type == T_SYMBOL) {
        currentFlow.push_back(new SymbolElement(it->data));
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
          (*this->outputStream) << (*command)->eval(this->globalContext)->value() << ' ';
        }
        (*this->outputStream) << '\n';
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
      catch (NotFunctionContextException e) {
        (*this->outputStream) << "[ERROR] Symbol '"<< e.sym <<"' is a variable, not a function.\n";
      }
      catch (UnknownSymbolContextException e) {
        (*this->outputStream) << "[ERROR] Symbol '" << e.sym << "' is unknown.\n";
      }
      catch (ExitTrap e) {
        (*this->outputStream) << "Good bye!\n";
        break;
      }
      catch (Exception e) {
        (*this->outputStream) << "[ERROR] Unknown error.\n";
      }
    } while (!this->inputStream->eof());
  }
};

