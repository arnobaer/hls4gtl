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
 *
 * Note: apply array partitions on member: data
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

   reference front()
   {
       return data[0];
   }

   const_reference front() const
   {
       return data[0];
   }

   reference back()
   {
       return data[size - 1];
   }

   const_reference back() const
   {
       return data[size - 1];
   }

   // Fill array with value
   void fill(const value_type& value)
   {
      for (size_type i = 0; i < size; ++i)
      {
#pragma HLS UNROLL
          data[i] = value;
      }
   }
};

} // namespace utils
} // namespace gtl

#endif
