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

static_assert
  ( crc<32,koopman32()>().process_cstring("hello world") == 0x367bbd89
  , "Koopman32 CRC value for 'hello world' should be 0x367bbd89"
  );

static_assert
  ( crc<32,koopman32(),0xffffffff>().process_cstring(u8"Γεια σας κόσμο") == 0x725e7825
  , "Koopman32 CRC using initial remainder 0xffffffff value for 'Γεια σας κόσμο' should be 0x725e7825"
  );
