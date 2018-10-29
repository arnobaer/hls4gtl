#ifndef tb_unittest_logic_h
#define tb_unittest_logic_h

#include "../src/gtl/logic.h"
#include "../src/gtl/object.h"
#include "../src/gtl/cut.h"

#include "../src/gtl/utils/array.h"

#include <cassert>
#include <cstddef>

namespace unittest {

void logic_charge_correlation()
{
    using namespace gtl;

    const size_t size = 4;
    utils::array<object::muon, size> objects = {};

    logic::charge_correlation<objects.size> chgcorr;

    assert(chgcorr.size == size);
}

void logic_combination()
{
    using namespace gtl;

    typedef logic::combination<1> comb_single;
    typedef logic::combination<2> comb_double;

    // Single
    {
        utils::array<utils::array<bool, 8>, 1> matrix = {};
        bool result;

        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == false);

        matrix[0][3] = true;
        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == true);

        matrix[0][7] = true;
        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == true);

        matrix[0][0] = true;
        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == true);

        matrix[0].fill(false);
        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == false);

        matrix[0].fill(true);
        result = comb_single::slice<0, 7>::find(matrix);
        assert(result == true);
    }

    // Double
    {
        utils::array<utils::array<bool, 12>, 2> matrix = {};
        bool result;

        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == false);

        matrix[0][3] = true;
        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == false);

        matrix[1][3] = true;
        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == false);

        matrix[1][4] = true;
        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == true);

        matrix[0].fill(false);
        matrix[1].fill(false);
        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == false);

        matrix[0].fill(true);
        matrix[1].fill(true);
        result = comb_double::slice<0, 11>::find(matrix);
        assert(result == true);
    }
}

void logic_all()
{
    logic_charge_correlation();
    logic_combination();
}

} // namespace unittest

#endif
