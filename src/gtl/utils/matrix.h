#ifndef gtl_utils_matrix_h
#define gtl_utils_matrix_h

#include "array.h"

#include <cstddef>

namespace gtl {
namespace utils {

/* Container for fixed sized matrix.
 *
 * Example:
 * utils::matrix<unsigned, 2, 3> values;
 *
 * Note: apply array partitions on member: data
 */
template<typename T, size_t M, size_t N>
struct matrix
{
    typedef T value_type;
    typedef size_t size_type;

    static const size_type rows = M;
    static const size_type columns = N;

    value_type data[rows][columns];

    void init(const value_type& value)
    {
        for (size_type i = 0; i < rows; ++i)
#pragma HLS UNROLL
            for (size_type j = 0; j < columns; ++j)
#pragma HLS UNROLL
                data[i][j] = value;
    }
};

} // namespace utils
} // namespace gtl

#endif
