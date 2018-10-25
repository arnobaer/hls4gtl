#ifndef gtl_condition_esums_h
#define gtl_condition_esums_h

#include <ap_int.h>

namespace gtl {
namespace condition {

// Energy sums condition
struct esums
{
    typedef ap_uint<1> result_type;

    template<typename T1, typename T2>
    static result_type process(const T1& cut, const T2& data)
    {
  #pragma HLS INTERFACE ap_ctrl_none port=return
        return cut.comp(data);
    }
};

} // namespace condition
} // namespace gtl

#endif
