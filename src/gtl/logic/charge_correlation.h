#ifndef gtl_logic_charge_correlation_h
#define gtl_logic_charge_correlation_h

#include "../utils/math.h"
#include "../../definitions.h"

namespace gtl {
namespace logic {

// Charge correlation logic
//
// Example usage:
//
// gtl::logic::charge_correlation chgcorr_logic;
// chgcorr_logic.process(data.muon);
// comb(..., data.muon, chgcorr_logic);
//
struct charge_correlation
{
    typedef ap_uint<1> value_type;
    typedef value_type double_type[MAX_OBJ][MAX_OBJ];
    typedef value_type triple_type[MAX_OBJ][MAX_OBJ][MAX_OBJ];
    typedef value_type quad_type[MAX_OBJ][MAX_OBJ][MAX_OBJ][MAX_OBJ];

    // States
    enum {
      OS = false,
      LS = true,
    };

    double_type ls_double;
    triple_type ls_triple;
    quad_type ls_quad;

    template<typename T>
    void process(const T objects[MAX_OBJ])
    {
        // Almost insane optimization? Does it gain something?
        using utils::math::bitwidth;
        typedef ap_uint<bitwidth<MAX_OBJ>::value> iterator_type;

        for (iterator_type i = 0; i < MAX_OBJ; ++i)
        {
#pragma HLS unroll
            for (iterator_type j = 0; j < MAX_OBJ; ++j)
            {
#pragma HLS unroll
                ls_double[i][j] = OS;
                // TODO

                for (iterator_type k = 0; k < MAX_OBJ; ++k)
                {
#pragma HLS unroll
                    ls_triple[i][j][k] = OS;
                    // TODO

                    for (iterator_type l = 0; l < MAX_OBJ; ++l)
                    {
#pragma HLS unroll
                        ls_quad[i][j][k][l] = OS;
                        // TODO
                    }
                }
            }
        }
    }
};

} // namespace logic
} // namespace gtl

#endif
