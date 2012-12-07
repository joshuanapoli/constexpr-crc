#pragma once
#include <crc/initialized_array.hpp>
#include <crc/crc_table_item.hpp>
#include <boost/integer.hpp>

namespace crc
{
  // Table-based CRC calculator.
  template<std::size_t Bits, typename boost::uint_t<Bits>::fast Polynomial, typename boost::uint_t<Bits>::fast InitialRemainder=0>
  class crc
  {
  public:
    typedef typename boost::uint_t<Bits>::fast remainder_type;
  
    crc() : table_( crc_table_item<Bits,Polynomial>() ) {}

    template<typename T>
    constexpr remainder_type operator()(const T & object) const
    {
      return (*this)(reinterpret_cast<const uint8_t *>(&object), reinterpret_cast<const uint8_t *>(&object + 1));
    }

    template<typename Iterator>
    constexpr remainder_type operator()(Iterator first, Iterator last, remainder_type accumulator = InitialRemainder) const
    {
      return first < last 
        ? (*this)(first+1, last, (accumulator << 8) ^ table_[((accumulator >> (Bits-8)) ^ *first)&0xff])
        : accumulator;
    }

  private:
    initialized_array<remainder_type, 256> table_;
  };
}
