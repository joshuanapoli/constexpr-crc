#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <array>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <crc/crc.hpp>
#include <boost/crc.hpp>

bool init_unit_test()
{
  return true;
}

constexpr uint32_t koopman32()
{
  return 0x741B8CD7;
}

constexpr uint32_t koopman8()
{
  return 0x4d;
}

BOOST_AUTO_TEST_CASE( constexpr_32_bit_crc_has_same_result_as_boost_crc )
{
  char message[] = "hello world";

  boost::crc_optimal<32, koopman32()> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc::crc<32,koopman32()> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc( message )
    , boost_crc.checksum()
    );
}

BOOST_AUTO_TEST_CASE( constexpr_32_bit_crc_has_same_result_as_boost_crc_with_initial_remainder )
{
  char message[] = "hello world";

  boost::crc_optimal<32, koopman32(), 0xffffffff> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc::crc<32, koopman32(), 0xffffffff> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc( message )
    , boost_crc.checksum()
    );
}

BOOST_AUTO_TEST_CASE( constexpr_8_bit_crc_has_same_result_as_boost_crc )
{
  char message[] = "hello world";

  boost::crc_optimal<8,koopman8()> boost_crc;
  boost_crc.process_bytes( message, sizeof( message ) );

  crc::crc<8,koopman8()> constexpr_crc;

  BOOST_CHECK_EQUAL
    ( constexpr_crc( message )
    , boost_crc.checksum()
    );
}
