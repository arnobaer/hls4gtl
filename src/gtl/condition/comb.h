#ifndef gtl_condition_comb_h
#define gtl_condition_comb_h

#include "../logic/charge_correlation.h"
#include "../logic/combination.h"

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

        //matrix.fill(true);

        for (size_type i = 0; i < cuts_type::size; ++i)
        {
            matrix[i].fill(true);
#pragma HLS UNROLL
            for (size_type j = slice_minimum; j <= slice_maximum; ++j)
#pragma HLS UNROLL
                matrix[i][j] = cuts[i].comp(objects[j]);
        }
    }

    template<typename T1, typename T2>
    static result_type process(const T1& cuts, const T2& objects)
    {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS ARRAY_PARTITION variable=cuts.data complete dim=0
#pragma HLS ARRAY_PARTITION variable=objects.data complete dim=0

        typedef T1 cuts_type;
        typedef T2 objects_type;

        static const size_t dim = cuts_type::size;

        utils::array<utils::array<result_type, objects_type::size>, cuts_type::size> matrix;
        calc_matrix(cuts, objects, matrix);

        // NOTE
        //
        // logic::combination<cuts_type::size> will only work with C++11 constexpr feature!
        //
        // Workaround:
        switch (cuts_type::size)
        {
            case 1: return logic::combination<1>::slice<slice_minimum, slice_maximum>::find(matrix);
            case 2: return logic::combination<2>::slice<slice_minimum, slice_maximum>::find(matrix);
            case 3: return logic::combination<3>::slice<slice_minimum, slice_maximum>::find(matrix);
            case 4: return logic::combination<4>::slice<slice_minimum, slice_maximum>::find(matrix);
        }
        return false;
    }
};

} // namespace condition
} // namespace gtl

#endif
