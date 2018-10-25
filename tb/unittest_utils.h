#ifndef tb_unittest_utils_h
#define tb_unittest_utils_h

#include "../src/gtl/utils/iterator.h"
#include "../src/gtl/utils/math.h"
#include "../src/gtl/utils/range.h"

#include <cassert>

namespace unittest {

void utils_iterator()
{
    using namespace gtl;

    size_t values[4] = {42, 7, 0, 28};
    assert(utils::size(values) == 4);
    assert(utils::first(values) == 42);
    assert(utils::last(values) == 28);
}

void utils_math()
{
    using namespace gtl::utils;

    assert((math::pow<0, 0>::value) == 1);
    assert((math::pow<0, 1>::value) == 0);
    assert((math::pow<1, 0>::value) == 1);
    assert((math::pow<1, 1>::value) == 1);
    assert((math::pow<0, 2>::value) == 0);
    assert((math::pow<2, 0>::value) == 1);
    assert((math::pow<2, 1>::value) == 2);
    assert((math::pow<2, 2>::value) == 4);
    assert((math::pow<1, 4>::value) == 1);
    assert((math::pow<2, 8>::value) == 256);
    assert((math::pow<4, 2>::value) == 16);

    assert((math::bitwidth<0>::value) == 1);
    assert((math::bitwidth<1>::value) == 1);
    assert((math::bitwidth<2>::value) == 2);
    assert((math::bitwidth<3>::value) == 2);
    assert((math::bitwidth<4>::value) == 3);
    assert((math::bitwidth<42>::value) == 6);
}

void utils_range()
{
    using namespace gtl::utils;

    {
        range<size_t> r = {};
        assert(r.minimum == 0);
        assert(r.maximum == 0);
    }
    {
        range<size_t> r = {8, 42};
        assert(r.minimum == 8);
        assert(r.maximum == 42);
    }
    {
        range<size_t> r;
        r.minimum = 4;
        r.maximum = 8;
        assert(r.minimum == 4);
        assert(r.maximum == 8);
    }
}

void utils_all()
{
    utils_iterator();
    utils_math();
    utils_range();
}

} // namespace unittest

#endif
