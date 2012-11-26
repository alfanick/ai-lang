#include "AILang.h"

#include "RpnParser.h"

int main() {
  setlocale(LC_ALL, "C");
  AI::RpnParser::getInstance().loop();

  return 0;
}
