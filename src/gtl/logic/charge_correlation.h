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
// gtl::logic::charge_correlation<12> chgcorr_logic;
// chgcorr_logic.process(data.muon);
// comb(..., data.muon, chgcorr_logic);
//
template<size_t N>
struct charge_correlation
{
    typedef ap_uint<2> value_type;
    typedef size_t size_type;

    static const size_type size = N;

    typedef value_type double_type[size][size];
    typedef value_type triple_type[size][size][size];
    typedef value_type quad_type[size][size][size][size];

    // States
    enum {
      IGNORE,
      OS,
      LS,
    };

    double_type state_double;
    triple_type state_triple;
    quad_type state_quad;

    template<typename T>
    void process(const T objects[size])
    {
        // Almost insane optimization? Does it gain something?
        using utils::math::bitwidth;
        typedef ap_uint<bitwidth<size>::value> iterator_type;

        // charge bits
        static const size_type sign = 0;
        static const size_type valid = 1;

        for (iterator_type i = 0; i < size; ++i)
        {
#pragma HLS unroll
            for (iterator_type j = 0; j < size; ++j)
            {
#pragma HLS unroll
                state_double[i][j] = IGNORE;
                if (objects[i].charge[valid] and objects[j].charge[valid])
                {
                    if (objects[i].charge[sign] == objects[j].charge[sign])
                    {
                        state_double[i][j] = LS;
                    }
                    else
                    {
                        state_double[i][j] = OS;
                    }
                }

                for (iterator_type k = 0; k < size; ++k)
                {
#pragma HLS unroll
                    state_triple[i][j][k] = IGNORE;
                    if (objects[i].charge[valid] and objects[j].charge[valid] and objects[k].charge[valid])
                    {
                        if (objects[i].charge[sign] == objects[j].charge[sign] and
                            objects[i].charge[sign] == objects[k].charge[sign])
                        {
                            state_triple[i][j][k] = LS;
                        }
                        else
                        {
                            state_triple[i][j][k] = OS;
                        }
                    }

                    for (iterator_type l = 0; l < size; ++l)
                    {
#pragma HLS unroll
                        state_quad[i][j][k][l] = IGNORE;
                        if (objects[i].charge[valid] and objects[j].charge[valid] and objects[k].charge[valid] and objects[l].charge[valid])
                        {
                            if (objects[i].charge[sign] == objects[j].charge[sign] and
                                objects[i].charge[sign] == objects[k].charge[sign] and
                                objects[i].charge[sign] == objects[l].charge[sign])
                            {
                                state_quad[i][j][k][l] = LS;
                            }
                            else
                            {
                                state_quad[i][j][k][l] = OS;
                            }
                        }
                    }
                }
            }
        }
    }
};

} // namespace logic
} // namespace gtl

#endif
