#include "NumberElement.h"

namespace AI {
  NumberElement::NumberElement(std::string data) : StringElement(data) {
    this->mp_value = new mpf_class(data, 1024, 10);
  };

  NumberElement::~NumberElement() {
    delete this->mp_value;
  }

  std::string NumberElement::value() {
    mp_exp_t t = 0;
    std::string tmp = this->mp_value->get_str(t);
    if (t == 0 && tmp.size() == 0)
      return "0";
    if (tmp[0] == '-')
      t++;
    if (t < tmp.size())
      tmp.insert(t, ".");
    else if (tmp.size() < t) {
      do {
        tmp += "0";
      } while(tmp.size() != t);
    }
    if ((tmp[0] == '-' && t == 1) || t == 0) {
      tmp.insert(t, "0");
    }
    return tmp;
  }

  NumberElement* NumberElement::eval(Context* localContext) {
    return this;
  }

};
