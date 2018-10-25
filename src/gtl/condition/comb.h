#ifndef gtl_condition_comb_h
#define gtl_condition_comb_h

#include "../logic/charge_correlation.h"

#include "../utils/array.h"
#include "../utils/matrix.h"

namespace gtl {
namespace condition {

template<size_t SLICE_MIN, size_t SLICE_MAX>
struct comb
{
    typedef size_t size_type;
    typedef ap_uint<1> result_type;

    static const size_type slice_minimum = SLICE_MIN;
    static const size_type slice_maximum = SLICE_MAX;

    template<typename T1, typename T2, typename T3>
    static void calc_matrix(const T1& cuts, const T2& objects, T3& matrix)
    {
#pragma HLS INTERFACE ap_ctrl_none port=data
#pragma HLS ARRAY_PARTITION variable=cuts.data complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects.data complete dim=0
#pragma HLS ARRAY_PARTITION variable=matrix.data complete dim=0

        typedef T1 cuts_type;

        matrix.init(true);

        for (size_type i = 0; i < cuts_type::size; ++i)
#pragma HLS UNROLL
            for (size_type j = slice_minimum; j <= slice_maximum; ++j)
#pragma HLS UNROLL
                matrix.data[i][j] = cuts[i].comp(objects[j]);
    }

    template<typename T>
    static result_type reduce_matrix_single(const T& matrix)
    {
        result_type result = false;
        for (size_type i = slice_minimum; i <= slice_maximum; ++i)
        {
#pragma HLS UNROLL
            result |= matrix.data[0][i];
        }
        return result;
    }

    template<typename T>
    static result_type reduce_matrix_double(const T& matrix)
    {
        result_type result = false;
        for (size_type i = slice_minimum; i <= slice_maximum; ++i)
        {
#pragma HLS UNROLL
            for (size_type j = slice_minimum; j <= slice_maximum; ++j)
            {
#pragma HLS UNROLL
                if (i != j)
                {
                    result |= matrix.data[0][i] and matrix.data[1][j];
                }
            }
        }
        return result;
    }

    template<typename T>
    static result_type reduce_matrix_triple(const T& matrix)
    {
        result_type result = false;
        for (size_type i = slice_minimum; i <= slice_maximum; ++i)
        {
#pragma HLS UNROLL
            for (size_type j = slice_minimum; j <= slice_maximum; ++j)
            {
#pragma HLS UNROLL
                for (size_type k = slice_minimum; k <= slice_maximum; ++k)
                {
#pragma HLS UNROLL
                    if (i != j and j != k and i != k)
                    {
                        result |= matrix.data[0][i] and matrix.data[1][j] and matrix.data[2][k];
                    }
                }
            }
        }
        return result;
    }

    template<typename T>
    static result_type reduce_matrix_quad_partial(size_t i, const T& matrix)
    {
        result_type result = false;
        for (size_type j = slice_minimum; j <= slice_maximum; ++j)
        {
#pragma HLS UNROLL
            for (size_type k = slice_minimum; k <= slice_maximum; ++k)
            {
#pragma HLS UNROLL
                for (size_type l = slice_minimum; l <= slice_maximum; ++l)
                {
#pragma HLS UNROLL
                    if (i != j and j != k and k != l and i != k and i != l)
                    {
                        result |= matrix.data[0][i] and matrix.data[1][j] and matrix.data[2][k] and matrix.data[3][l];
                    }
                }
            }
        }
        return result;
    }

    template<typename T>
    static result_type reduce_matrix_quad(const T& matrix)
    {
        result_type result = false;
        for (size_type i = slice_minimum; i <= slice_maximum; ++i)
        {
#pragma HLS UNROLL
            result |= reduce_matrix_quad_partial(i, matrix);
        }
        return result;
    }

    template<typename T1, typename T2>
    static result_type process(const T1& cuts, const T2& objects)
    {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=cuts.data complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects.data complete dim=0

        typedef T1 cuts_type;
        typedef T2 objects_type;

        utils::matrix<result_type, cuts_type::size, objects_type::size> matrix;

        // calculate matrix
        calc_matrix(cuts, objects, matrix);

        // reduce matrix
        switch (cuts_type::size)
        {
            case 1: return reduce_matrix_single(matrix);
            case 2: return reduce_matrix_double(matrix);
            case 3: return reduce_matrix_triple(matrix);
            case 4: return reduce_matrix_quad(matrix);
            default: return false;
        }
    }
};

} // namespace condition
} // namespace gtl

#endif
