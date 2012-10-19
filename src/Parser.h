#ifndef AI_PARSER_FILE
#define AI_PARSER_FILE

#include <iostream>

#include "Context.h"

namespace AI {
  class Parser {
    public:
      Context *systemContext;
      Context *masterContext;

      Parser(std::istream& in, std::ostream& out);
      ~Parser();

      void* parse(std::string);
      void loop();

      static Parser& getInstance() {
        static Parser instance (std::cin, std::cout);
        return instance;
      }

    private:
      std::istream *inputStream;
      std::ostream *outputStream;

      std::string askForInput();
      std::string writeOutput();
  };
};

#endif
