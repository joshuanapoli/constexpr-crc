#pragma once
#include <boost/integer.hpp>

template<std::size_t Bits, typename boost::uint_t<Bits>::fast Polynomial>
class crc_table_item
{
public:
  typedef typename boost::uint_t<Bits>::fast value_type;

  constexpr value_type operator()( std::size_t n )
  {
    return calculate_remainder(initial_remainder(n));
  }

private:
  static constexpr value_type bit_width()
  {
    return Bits;
  }

  static constexpr value_type initial_remainder(std::size_t n)
  {
    return n << (bit_width()-8);
  }

  static constexpr value_type calculate_remainder(value_type remainder, int bit = 0)
  {
    return bit < 8
      ? calculate_remainder(mod_shift(remainder), bit+1)
      : remainder
      ;
  }

  static constexpr value_type mod_shift(value_type x)
  {
    return x & (1 << (bit_width()-1))
      ? (x << 1) ^ Polynomial
      : x << 1
      ;
  }
};
