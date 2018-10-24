#ifndef gtl_utils_array_h
#define gtl_utils_array_h

#include <cassert>
#include <cstddef>

namespace gtl {
namespace utils {

/* Container for fixed sized array.
 *
 * Example:
 * utils::array<unsigned, 8> values;
 */
template<typename T, size_t N>
struct array
{
   typedef T value_type;
   typedef size_t size_type;
   typedef value_type& reference;
   typedef const value_type& const_reference;

   static const size_type size = N;

   value_type data[size];

   reference operator[](size_type pos)
   {
       assert(pos < size);
       return data[pos];
   }

   const_reference operator[](size_type pos) const
   {
       assert(pos < size);
       return data[pos];
   }

   const_reference front() const
   {
       return data[0];
   }

   const_reference back() const
   {
       return data[size - 1];
   }
};

} // namespace utils
} // namespace gtl

#endif
