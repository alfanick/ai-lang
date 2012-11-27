#include "AILang.h"

#include "Parser.h"

int main() {
  setlocale(LC_ALL, "C");
  AI::Parser::getInstance().loop();

  return 0;
}
