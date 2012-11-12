#pragma once
#include <array>

// Table-based 32-bit CRC calculator.
template<uint32_t Polynomial>
class Crc
{
public:
  typedef uint32_t remainder_type;
  typedef std::array<remainder_type,256> table_type;
  
  constexpr Crc()
    : table_{{create_table}}
  {}

  template<class Iterator>
  constexpr remainder_type process_bytes(Iterator first, Iterator last, remainder_type accumulator = 0) const
  {
    return first < last 
      ? process_bytes(first+1, last, (accumulator << 8) ^ table_[(accumulator >> 24) ^ *first])
      : accumulator;
  }

private:
  struct table_item
  {
    constexpr bit_width()
    {
      return 32;
    }

    constexpr table_item(uint8_t n)
      : value(calculate_remainder(n << (bit_width()-8)))
    {
    }

    constexpr calculate_remainder(remainder_type remainder, int bit = 0)
    {
      return bit < 8
        ? calculate_remainder(mod_shift(remainder), bit+1)
        : remainder
        ;
    }

    constexpr mod_shift(uint32_t x)
    {
      return x & (1 << (bit_width()-1)
        ? (x << 1) ^ Polynomial
        : x << 1
        ;
    }
    
    remainder_type value;
  };

  template<typename i = sequence<0,256>()>
  static constexpr table_type generate_table()
  {
    return table_type{{ table_item(i)... }}
  }
  
  remainder_type table_[256];
};
