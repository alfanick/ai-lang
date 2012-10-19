#ifndef AI_PARSER_FILE
#define AI_PARSER_FILE

#include <iostream>
#include <vector>

#include "Context.h"
#include "Tokenizer.h"

namespace AI {
  /**
   * Main parser.
   *
   * Manages system context and global context. Creates
   * interpreter, parses single commands using Tokenizer.
   */
  class Parser {
    public:
      /**
       * System context.
       *
       * Includes system functions such as operators and IO.
       * These are not overridable.
       */
      Context *systemContext;

      /**
       * Global context.
       *
       * Creates space for runtime symbols.
       * These are overridable. If symbol exist in globalContext,
       * it is used instead of systemContext.
       */
      Context *globalContext;

      /**
       * Constructor.
       *
       * Creates interpreter using given input and output streams.
       */
      Parser(std::istream& in, std::ostream& out);

      /**
       * Destructor.
       *
       * Cleans contexts.
       */
      ~Parser();

      /**
       * Parse tokens and return output.
       */
      std::string parse(std::vector<token>);

      /**
       * Creates interpeter loop.
       *
       * Asks for input using simple prompt. Commands must
       * end with semicolon, then it parses the command and
       * returns output.
       *
       * Everything is executed inside globalContext.
       */
      void loop();

      /**
       * Return instance of Parser using stdio and stdout.
       *
       * Implements Singleton pattern.
       */
      static Parser& getInstance() {
        static Parser instance (std::cin, std::cout);
        return instance;
      }

    private:
      // Input stream used for parsing
      std::istream *inputStream;
      // Output steam used for writing results
      std::ostream *outputStream;
  };
};

#endif
