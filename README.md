constexpr-crc
=============

This is a C++11 table-driven CRC calculator. The table is a constant expression
suitable for ROM, generated using the [constexpr table library](table). The CRC
algorithm is also constexpr, so the check code for static messages can be
evaluated at compile time. Here are examples for using the library:

```c++
#include <crc.hpp>

BOOST_AUTO_TEST_CASE( hello_world )
{
  char message[] = "hello world";
  BOOST_CHECK_EQUAL
    ( crc<32,koopman32()>().process_bytes("hello world", sizeof(message))
    , 0x367bbd89
    );
}

static_assert
  ( crc<32,koopman32(),0xffffffff>().process_cstring(u8"Γεια σας κόσμο") == 0x725e7825
  , "Koopman32 CRC using initial remainder 0xffffffff value for 'Γεια σας κόσμο' should be 0x725e7825"
  );

```

The constexpr-crc library is a header only library, so there is no object file
to build or link. The library depends on Boost to calculate an integer type. A
Boost Build Jamfile is included that builds the unit test.

The library requires compiler support for aggregate initialization. Version 4.7 or higher of GCC will work.
