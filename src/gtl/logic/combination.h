#ifndef gtl_logic_combination_h
#define gtl_logic_combination_h

#include <cstddef>

#include <ap_int.h>

namespace gtl {
namespace logic {

template<size_t N>
struct combination
{
  void find() {}
};

// Single (non-)combination
template<>
struct combination<1>
{
    typedef size_t size_type;
    typedef bool result_type;

    template<size_type SLICE_MIN, size_type SLICE_MAX>
    struct slice
    {
        static const size_type slice_minimum = SLICE_MIN;
        static const size_type slice_maximum = SLICE_MAX;

        template<typename T>
        static bool find(const T& matrix)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0

            bool result = false;
            for (size_type i = slice_minimum; i <= slice_maximum; ++i)
            {
#pragma HLS UNROLL
                result |= matrix[0][i];
            }
            return result;
        }
    };
};

// Double combination
template<>
struct combination<2>
{
    typedef size_t size_type;
    typedef bool result_type;

    template<size_type SLICE_MIN, size_type SLICE_MAX>
    struct slice
    {
        static const size_type slice_minimum = SLICE_MIN;
        static const size_type slice_maximum = SLICE_MAX;

        template<typename T>
        static result_type find(const T& matrix)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0

            result_type result = false;
            for (size_type i = slice_minimum; i <= slice_maximum; ++i)
            {
#pragma HLS UNROLL
                for (size_type j = slice_minimum; j <= slice_maximum; ++j)
                {
#pragma HLS UNROLL
                    if (i != j)
                    {
                        result |= matrix[0][i] and matrix[1][j];
                    }
                }
            }
            return result;
        }

        template<typename T1, typename T2>
        static result_type find(const T1& matrix, const T2& charge_correlation)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0
#pragma HLS ARRAY_PARTITION variable=charge_correlation.data dim=0

            result_type result = false;
            for (size_type i = slice_minimum; i <= slice_maximum; ++i)
            {
#pragma HLS UNROLL
                for (size_type j = slice_minimum; j <= slice_maximum; ++j)
                {
#pragma HLS UNROLL
                    if (i != j)
                    {
                        result |= matrix[0][i] and matrix[1][j] and charge_correlation[i][j];
                    }
                }
            }
            return result;
        }
    };
};

// Triple combination
template<>
struct combination<3>
{
    typedef size_t size_type;
    typedef bool result_type;

    template<size_type SLICE_MIN, size_type SLICE_MAX>
    struct slice
    {
        static const size_type slice_minimum = SLICE_MIN;
        static const size_type slice_maximum = SLICE_MAX;

        template<typename T>
        static result_type find(const T& matrix)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0

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
                            result |= matrix[0][i] and matrix[1][j] and matrix[2][k];
                        }
                    }
                }
            }
            return result;
        }

        template<typename T1, typename T2>
        static result_type find(const T1& matrix, const T2& charge_correlation)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0
#pragma HLS ARRAY_PARTITION variable=charge_correlation.data dim=0

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
                            result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and charge_correlation[i][j][k];
                        }
                    }
                }
            }
            return result;
        }
    };
};

// Quad combination
template<>
struct combination<4>
{
    typedef size_t size_type;
    typedef bool result_type;

    template<size_type SLICE_MIN, size_type SLICE_MAX>
    struct slice
    {
        static const size_type slice_minimum = SLICE_MIN;
        static const size_type slice_maximum = SLICE_MAX;

        template<typename T>
        static result_type find_partial(const size_type i, const T& matrix)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0

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
                            result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l];
                        }
                    }
                }
            }
            return result;
        }

        template<typename T1, typename T2>
        static result_type find_partial(const size_type i, const T1& matrix, const T2& charge_correlation)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0
#pragma HLS ARRAY_PARTITION variable=charge_correlation.data dim=0

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
                            result |= matrix[0][i] and matrix[1][j] and matrix[2][k] and matrix[3][l] and charge_correlation[i][j][k][l];
                        }
                    }
                }
            }
            return result;
        }

        template<typename T>
        static result_type find(const T& matrix)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0

            result_type result = false;
            for (size_type i = slice_minimum; i <= slice_maximum; ++i)
            {
#pragma HLS UNROLL
                result |= find_partial(i, matrix);
            }
            return result;
        }

        template<typename T1, typename T2>
        static result_type find(const T1& matrix, const T2& charge_correlation)
        {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=matrix.data dim=0
#pragma HLS ARRAY_PARTITION variable=charge_correlation.data dim=0

            result_type result = false;
            for (size_type i = slice_minimum; i <= slice_maximum; ++i)
            {
#pragma HLS UNROLL
                result |= find_partial(i, matrix, charge_correlation);
            }
            return result;
        }
    };
};

} // namespace logic
} // namespace gtl

#endif
