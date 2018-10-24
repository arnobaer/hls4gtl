#ifndef gtl_utils_iterator_h
#define gtl_utils_iterator_h

#include <cstddef>

namespace gtl {
namespace utils {

/* Returns size of C array.
 *
 * Example:
 * unsigned values[8];
 * utils::size(values); // returns 8
 */
template<typename T, size_t N>
inline size_t size(const T (&)[N])
{
    return N;
}

/* Returns constant reference to first element of array.
 *
 * Example:
 * unsigned values[4] = {42, 43, 44, 45};
 * utils::first(values); // returns 42
 */
template<typename T, size_t N>
inline const T& first(const T (&data)[N])
{
    return data[0];
}

/* Returns constant reference to last element of array.
 *
 * Example:
 * unsigned values[4] = {42, 43, 44, 45};
 * utils::last(values); // returns 45
 */
template<typename T, size_t N>
inline const T& last(const T (&data)[N])
{
    return data[N - 1];
}

} // namespace utils
} // namespace gtl

#endif
