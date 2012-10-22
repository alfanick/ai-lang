#include "AILang.h"

int main() {
  setlocale(LC_ALL, "C");
  AI::Parser::getInstance().loop();

  return 0;
}
