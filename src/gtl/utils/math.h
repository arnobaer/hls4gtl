#ifndef gtl_utils_math_h
#define gtl_utils_math_h

#include <cstddef>

namespace gtl {
namespace utils {
namespace math {

// Computes the value of A raised to the power B
template <size_t A, size_t B>
struct pow
{
    static const size_t value = A * pow<A, B - 1>::value;
};

template <size_t A>
struct pow<A, 0>
{
    static const size_t value = 1;
};

// Retruns number of bits required to store value A
template <size_t A>
struct bitwidth
{
    static const size_t value = 1 + bitwidth<(A >> 1)>::value;
};

template <>
struct bitwidth<0>
{
    static const size_t value = 0;
};

} // namespace math
} // namespace utils
} // namespace gtl

#endif
