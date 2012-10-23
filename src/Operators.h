#ifndef AI_OPERATORS_FILE
#define AI_OPERATORS_FILE

#include "Context.h"
#include "Element.h"
#include "NumberElement.h"
#include "StringElement.h"

namespace AI {
  /**
   * Native operators implementation.
   */
	namespace Operators {
		Element* o_or(Context* args);

		Element* o_and(Context* args);

		Element* bit_or(Context* args);

		Element* bit_xor(Context* args);

		Element* bit_and(Context* args);

		Element* not_equal(Context* args);

		Element* equal(Context* args);

		Element* greater_equal(Context* args);

		Element* greater(Context* args);

		Element* less_equal(Context* args);

		Element* less(Context* args);

		Element* bit_shift_right(Context* args);

		Element* bit_shift_left(Context* args);

		Element* subtract(Context* args);

		Element* add(Context* args);

		Element* modulo(Context* args);

		Element* divide(Context* args);

		Element* multiply(Context* args);

		Element* o_not(Context* args);

		Element* bit_not(Context* args);
	};
};

#endif
