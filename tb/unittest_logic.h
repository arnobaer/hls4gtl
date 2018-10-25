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

void logic_all()
{
    logic_charge_correlation();
}

} // namespace unittest

#endif
