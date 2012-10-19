#ifndef AI_TOKENIZER_FILE
#define AI_TOKENIZER_FILE

namespace AI {
  class Tokenizer {
    public:
      static Tokenizer& getInstance() {
        static Tokenizer instance;
        return instance;
      }
  };
};

#endif
