#pragma once
#include <table.hpp>
#include <detail/table_value.hpp>

// Table-based CRC calculator.
template<std::size_t Bits, typename boost::uint_t<Bits>::fast Polynomial, typename boost::uint_t<Bits>::fast InitialRemainder=0>
class crc
{
public:
  typedef typename boost::uint_t<Bits>::fast remainder_type;
  
  constexpr crc() : table_( detail::table_value<Bits,Polynomial>() ) {}

  template<std::size_t size>
  constexpr remainder_type process_cstring( const char (& cstring)[size] ) const
  {
    return this->process_bytes( &cstring[0], size );
  }

  constexpr remainder_type process_bytes( const char* first, std::size_t size, remainder_type accumulator = InitialRemainder ) const
  {
    return 0 < size
      ? this->process_bytes( first+1, size-1, (accumulator << 8) ^ table_[ ((accumulator >> (Bits-8)) ^ *first) &0xff ] )
      : accumulator;
  }

private:
  table<remainder_type, 256> table_;
};

constexpr uint32_t koopman32()
{
  return 0x741B8CD7;
}

constexpr uint32_t koopman8()
{
  return 0x4d;
}

constexpr uint32_t ccit()
{
  return 0x1021;
}

constexpr uint32_t crc16()
{
  return 0x8005;
}

constexpr uint32_t crc32()
{
  return 0x04C11DB7;
}

// Computation type for ARC|CRC-16|CRC-IBM|CRC-16/ARC|CRC-16/LHA standard
//typedef crc<16, crc16(), 0, 0, true, true>         crc_16_type;

// Computation type for the KERMIT|CRC-16/CCITT|CRC-16/CCITT-TRUE|CRC-CCITT standard
//typedef crc<16, ccit(), 0, 0, true, true>         crc_ccitt_true_t;

// Computation type for the XMODEM|ZMODEM|CRC-16/ACORN standard
typedef crc<16, ccit()> crc_xmodem_t;

// Computation type for CRC-32|CRC-32/ADCCP|PKZIP standard
//typedef crc<32, crc32(), 0xFFFFFFFF, 0xFFFFFFFF, true, true> crc_32_type;

static_assert
  ( crc<32,koopman32()>().process_cstring("hello world") == 0x367bbd89
  , "Koopman32 CRC value for 'hello world' should be 0x367bbd89"
  );

static_assert
  ( crc<32,koopman32(),0xffffffff>().process_cstring(u8"Γεια σας κόσμο") == 0x725e7825
  , "Koopman32 CRC using initial remainder 0xffffffff value for 'Γεια σας κόσμο' should be 0x725e7825"
  );
