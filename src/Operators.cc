#include "Operators.h"

namespace AI {
	namespace Operators {
		Element* o_or(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si() != 0
          ||
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si() != 0
			);
		}

		Element* o_and(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si() != 0
          &&
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si() != 0
			);
		}

		Element* bit_or(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          |
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* bit_xor(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          ^
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* bit_and(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          &
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* not_equal(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          !=
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}


		Element* equal(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          ==
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* greater_equal(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          >=
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* greater(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          >
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* less_equal(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          <=
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* less(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          <
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* bit_shift_right(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          >>
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* bit_shift_left(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          <<
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* subtract(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          -
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* add(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          +
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* modulo(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si()
          %
        ((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)->get_si()
			);
		}

		Element* divide(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          /
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* multiply(Context* args) {
			return NumberElement::create(
        *((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)
          *
        *((dynamic_cast<NumberElement*>(args->getSymbol("$2")->eval(args)))->mp_value)
			);
		}

		Element* o_not(Context* args) {
			return NumberElement::create(
        ((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si() == 0
			);
		}

		Element* bit_not(Context* args) {
			return NumberElement::create(
        ~ (((dynamic_cast<NumberElement*>(args->getSymbol("$1")->eval(args)))->mp_value)->get_si())
			);
		}
	};
};
